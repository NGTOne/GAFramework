#include "nodes/EANode/systems/ES/MuLambdaES.hpp"
#include "core/utils/HierGC.hpp"
#include "nodes/EANode/mutations/GaussianMutation.hpp"
#include "loci/NumericSetLocus.hpp"
#include <math.h>

MuLambdaES::AdjustableESMutation::AdjustableESMutation() {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
	this->tausCalculated = false;
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
}

Genome* MuLambdaES::AdjustableESMutation::mutate(Genome* initialGenome) {
	Genome* realInitial = initialGenome;
	if (
		this->initialGenomeLength == 0
		|| initialGenome->genomeLength() < this->targetGenomeLength
	) initialGenome = this->addStdDevs(initialGenome);

	std::vector<Gene*> adjusted =
		this->adjustStdDevs(initialGenome->getGenome());
	Genome* adjustedGenome =
		new Genome(adjusted, initialGenome->getSpeciesNode());
	std::vector<MutationOperation*> mutations =
		this->getMutations(adjustedGenome);


	std::vector<Gene*> results;
	for (unsigned int i = 0; i < initialGenome->genomeLength(); i++)
		results.push_back(
			this->newLocusValue(adjustedGenome, i, mutations[i])
		);

	this->cleanUpMutations(mutations);
	delete(initialGenome);
	delete(adjustedGenome);

	return new Genome(results, realInitial->getSpeciesNode());
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
	if (std::find(
		this->stdDevIndices.begin(),
		this->stdDevIndices.end(),
		index
	) == this->stdDevIndices.end()) {
		Genome* temp =
			new Genome({genes[index]}, current->getSpeciesNode());
		Genome* result = mutation->mutate(temp);
		Gene* resultGene = result->getGenome()[0]->copy();
		delete(result);
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
	std::vector<Gene*> initialGenes = target->getGenome();

	if (!this->tausCalculated) this->calculateTaus(target);
	if (this->initialGenomeLength == 0) {
		this->initialGenomeLength = target->genomeLength();
		this->targetGenomeLength = 2 * target->genomeLength();
	}

	for (unsigned int i = 0; i < initialGenes.size(); i++) {
		initialGenes.push_back(
			(new NumericSetLocus<double>())->getGene()
		);
		if (this->stdDevIndices.size() < this->initialGenomeLength)
			this->stdDevIndices.push_back(
				this->initialGenomeLength + i
			);
		HierGC::registerObject(
			initialGenes[initialGenes.size() + i]->getLocus()
		);
	}

	return new Genome(initialGenes, target->getSpeciesNode());
}

std::vector<Gene*> MuLambdaES::AdjustableESMutation::adjustStdDevs(
	std::vector<Gene*> genes
) {
	std::vector<Gene*> results;
	results.insert(
		results.begin(),
		genes.begin(),
		genes.begin() + this->initialGenomeLength
	);

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
			target->getIndex<double>(
				this->stdDevIndices[stdDevIndex++]
			)
		));

	return mutations;
}

void MuLambdaES::AdjustableESMutation::cleanUpMutations(
	std::vector<MutationOperation*> mutations
) {
	for (unsigned int i = 0; i < mutations.size(); i++)
		delete(mutations[i]);
}
