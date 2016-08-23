#include "nodes/EANode/mutations/AdaptiveRealValueMutation.hpp"
#include "core/utils/HierGC.hpp"
#include "loci/NumericSetLocus.hpp"
#include <math.h>
#include <limits>

AdaptiveRealValueMutation::AdaptiveRealValueMutation() {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
	this->tausCalculated = false;
	this->stdDevLocus = NULL;
	this->setupDone = false;
}

AdaptiveRealValueMutation::AdaptiveRealValueMutation(
	double tau,
	double tauPrime
) {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
	this->tau = tau;
	this->tauPrime = tauPrime;
	this->tausCalculated = true;
	this->stdDevLocus = NULL;
	this->setupDone = false;
}

Genome* AdaptiveRealValueMutation::mutate(Genome* initialGenome) {
	if (!this->setupDone) this->setupInternals(initialGenome);

	Genome* realInitial;
	if (
		this->targetGenomeLength == 0
		|| initialGenome->genomeLength() < this->targetGenomeLength
	) {
		realInitial = this->addStdDevs(initialGenome);
	} else {
		realInitial = new Genome(initialGenome);
	}

	Genome* mutated = this->mutateProper(realInitial);
	delete(realInitial);
	return mutated;
}

void AdaptiveRealValueMutation::setupInternals(Genome* firstTarget) {
	if (!this->tausCalculated) this->calculateTaus(firstTarget);
	if (!this->stdDevLocus) {
		this->stdDevLocus = new NumericSetLocus<double>(
			0,
			std::numeric_limits<double>::max()
		);
		HierGC::registerObject(this->stdDevLocus);
	}
	if (this->initialGenomeLength == 0) {
		this->initialGenomeLength = firstTarget->genomeLength();
		this->targetGenomeLength = 2 * firstTarget->genomeLength();
	}

	this->setupDone = true;
}

Gene* AdaptiveRealValueMutation::newLocusValue(Gene* current) {
	return NULL;
}

void AdaptiveRealValueMutation::calculateTaus(Genome* initial) {
	this->tau = pow(sqrt(2 * sqrt(initial->genomeLength())), -1);
	this->tauPrime = pow(sqrt(2 * initial->genomeLength()), -1);
	this->tausCalculated = true;
}

Genome* AdaptiveRealValueMutation::addStdDevs(Genome* target) {
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

Genome* AdaptiveRealValueMutation::mutateProper(Genome* target) {
	std::vector<Gene*> genes = target->getGenome();
	std::vector<Gene*> results;
	for (unsigned int i = 0; i < this->initialGenomeLength; i++)
		results.push_back(genes[i]->copy());

	double rhoZero = HierRNG::gaussian(0, 1);

	for (unsigned int index: this->stdDevIndices) {
		Gene* target = genes[index];
		double stdDev = target->getIndex();
		stdDev = stdDev * pow(
			stdDev,
			this->tauPrime * rhoZero
				+ this->tau * HierRNG::gaussian(0, 1)
		);
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