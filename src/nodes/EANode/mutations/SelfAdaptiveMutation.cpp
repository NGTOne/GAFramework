#include "nodes/EANode/mutations/SelfAdaptiveMutation.hpp"
#include "core/utils/HierRNG.hpp"
#include "loci/NumericSetLocus.hpp"

SelfAdaptiveMutation::SelfAdaptiveMutation(
	bool useTauPlusOneCorrection
) : AdaptiveRealValueMutation() {
	this->useTauPlusOneCorrection = useTauPlusOneCorrection;
}

SelfAdaptiveMutation::SelfAdaptiveMutation(
	double tau,
	double tauPrime,
	bool useTauPlusOneCorrection
) : AdaptiveRealValueMutation() {
	this->tau = tau;
	this->tauPrime = tauPrime;
	this->useTauPlusOneCorrection = useTauPlusOneCorrection;
	this->tausCalculated = true;
}

void SelfAdaptiveMutation::calculateTaus(Genome* initial) {
	this->tau = pow(sqrt(2 * sqrt(initial->genomeLength())), -1);
	this->tauPrime = pow(sqrt(2 * initial->genomeLength()), -1);
	this->tausCalculated = true;
}

void SelfAdaptiveMutation::calculateProperGenomeLengths(Genome* initial) {
	this->initialGenomeLength = initial->genomeLength();
	this->targetGenomeLength = initial->genomeLength() * 2;
}

Genome* SelfAdaptiveMutation::addStdDevs(Genome* target) {
	std::vector<Gene*> initialGenes = target->getGenomeCopy();

	for (unsigned int i = 0; i < this->initialGenomeLength; i++) {
		initialGenes.push_back(this->stdDevLocus->getGene(1));
		if (this->stdDevIndices.size() < this->initialGenomeLength)
			this->stdDevIndices.push_back(
				this->initialGenomeLength + i
			);
	}

	return new Genome(initialGenes, target->getSpeciesNode());
}

Genome* SelfAdaptiveMutation::mutateProper(Genome* target) {
	std::vector<Gene*> genes = target->getGenome();
	std::vector<Gene*> results;
	for (unsigned int i = 0; i < this->initialGenomeLength; i++)
		results.push_back(genes[i]->copy());

	double rhoZero = HierRNG::gaussian(0, 1);

	for (unsigned int index: this->stdDevIndices) {
		Gene* target = genes[index];
		double stdDev = target->getIndex();
		double tauResult = this->tauPrime * rhoZero
			+ this->tau * HierRNG::gaussian(0, 1);
		stdDev *= this->useTauPlusOneCorrection ?
			pow(stdDev, tauResult) : exp(tauResult);
		results.push_back(target->copy(stdDev));
	}

	for (unsigned int i = 0; i < this->initialGenomeLength; i++) {
		Gene* original = results[i];
		double newIndex = original->getIndex();
		newIndex = newIndex
			+ results[this->initialGenomeLength + i]->getIndex()
			* HierRNG::gaussian(0, 1);
		results[i] = original->copy(newIndex);
		delete(original);
	}

	return new Genome(results, target->getSpeciesNode());
}
