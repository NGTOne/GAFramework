#include "nodes/EANode/systems/ES/MuLambdaES.hpp"
#include "core/utils/HierGC.hpp"
#include "nodes/EANode/mutations/GaussianMutation.hpp"
#include "loci/NumericSetLocus.hpp"
#include <math.h>

MuLambdaES::AdjustableESMutation::AdjustableESMutation() {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
	this->tausCalculated = false;
	this->stdDevLocus = new NumericSetLocus<double>();
}

MuLambdaES::AdjustableESMutation::AdjustableESMutation(
	double tau,
	double tauPrime
) {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
	this->tau = tau;
	this->tauPrime = tauPrime;
	this->tausCalculated = true;
	this->stdDevLocus = new NumericSetLocus<double>();
}

Genome* MuLambdaES::AdjustableESMutation::mutate(Genome* initialGenome) {
	Genome* realInitial;
	if (
		this->targetGenomeLength == 0
		|| initialGenome->genomeLength() < this->targetGenomeLength
	) {
		realInitial = this->addStdDevs(initialGenome);
	} else {
		realInitial = new Genome(initialGenome);
	}

	std::vector<Gene*> adjusted =
		this->adjustStdDevs(realInitial->getGenome());
	Genome* adjustedGenome =
		new Genome(adjusted, realInitial->getSpeciesNode());
	std::vector<MutationOperation*> mutations =
		this->getMutations(adjustedGenome);

	std::vector<Gene*> results;
	for (unsigned int i = 0; i < initialGenome->genomeLength(); i++)
		results.push_back(
			this->newLocusValue(adjustedGenome, i, mutations[i])
		);

	this->cleanUpMutations(mutations);
	delete(realInitial);
	delete(adjustedGenome);

	return new Genome(results, initialGenome->getSpeciesNode());
}

void MuLambdaES::AdjustableESMutation::registerInternalObjects() {
	HierGC::registerObject(this->stdDevLocus);
}

Gene* MuLambdaES::AdjustableESMutation::newLocusValue(Gene* current) {
	return NULL;
}

Gene* MuLambdaES::AdjustableESMutation::newLocusValue(
	Genome* current,
	unsigned int index,
	MutationOperation* mutation
) {
	std::vector<Gene*> genes = current->getGenome();
	if (index < this->stdDevIndices[0]) {
		Genome* temp = new Genome(
			{genes[index]->copy()},
			current->getSpeciesNode()
		);
		Genome* result = mutation->mutate(temp);
		Gene* resultGene = result->getGenome()[0]->copy();
		delete(result);
		delete(temp);
		return resultGene;
	} else {
		return genes[index]->copy();
	}
}

void MuLambdaES::AdjustableESMutation::calculateTaus(Genome* initial) {
	this->tau = pow(sqrt(2 * sqrt(initial->genomeLength())), -1);
	this->tauPrime = pow(sqrt(2 * initial->genomeLength()), -1);
	this->tausCalculated = true;
}

Genome* MuLambdaES::AdjustableESMutation::addStdDevs(Genome* target) {
	std::vector<Gene*> initialGenes = target->getGenomeCopy();

	if (!this->tausCalculated) this->calculateTaus(target);
	if (this->initialGenomeLength == 0) {
		this->initialGenomeLength = target->genomeLength();
		this->targetGenomeLength = 2 * target->genomeLength();
	}

	for (unsigned int i = 0; i < this->initialGenomeLength; i++) {
		initialGenes.push_back(this->stdDevLocus->getGene());
		if (this->stdDevIndices.size() < this->initialGenomeLength)
			this->stdDevIndices.push_back(
				this->initialGenomeLength + i
			);
	}

	return new Genome(initialGenes, target->getSpeciesNode());
}

std::vector<Gene*> MuLambdaES::AdjustableESMutation::adjustStdDevs(
	std::vector<Gene*> genes
) {
	std::vector<Gene*> results;
	for (unsigned int i = 0; i < this->initialGenomeLength; i++)
		results.push_back(genes[i]->copy());

	double rhoZero = HierRNG::zeroOne<double>();

	for (unsigned int index: this->stdDevIndices) {
		Gene* target = genes[index];
		double stdDev = target->getIndex();
		stdDev = pow(
			stdDev,
			this->tauPrime * rhoZero
				+ this->tau * HierRNG::zeroOne<double>()
		);
		results.push_back(target->copy(stdDev));
	}

	return results;
}

std::vector<MutationOperation*> MuLambdaES::AdjustableESMutation::getMutations(
	Genome* target
) {
	std::vector<MutationOperation*> mutations;
	unsigned int stdDevIndex = 0;

	for (unsigned int i = 0; i < this->initialGenomeLength; i++)
		mutations.push_back(new GaussianMutation(
			0.0,
			target->getIndex<double>(
				this->stdDevIndices[stdDevIndex++]
			),
			1.0
		));

	return mutations;
}

void MuLambdaES::AdjustableESMutation::cleanUpMutations(
	std::vector<MutationOperation*> mutations
) {
	for (unsigned int i = 0; i < mutations.size(); i++)
		delete(mutations[i]);
}
