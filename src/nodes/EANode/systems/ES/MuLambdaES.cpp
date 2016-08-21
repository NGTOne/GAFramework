#include "nodes/EANode/systems/ES/MuLambdaES.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "core/utils/HierRNG.hpp"
#include "core/utils/HierGC.hpp"
#include "nodes/EANode/mutations/GaussianMutation.hpp"
#include <math.h>

MuLambdaES::MuLambdaES(
	MutationOperation* mutation,
	unsigned int lambda
) : ES(mutation) {
	this->init(lambda);
}

MuLambdaES::MuLambdaES(
	MutationOperation* mutation,
	SelectionStrategy* selection,
	unsigned int lambda
) : ES(selection, NULL, mutation) {
	this->init(lambda);
}

MuLambdaES::MuLambdaES(
	CrossoverOperation* cross,
	MutationOperation* mutation,
	unsigned int lambda,
	unsigned int rho
) : ES(cross, mutation) {
	this->init(lambda, rho);
}

MuLambdaES::MuLambdaES(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation,
	unsigned int lambda,
	unsigned int rho
) : ES(strategy, cross, mutation) {
	this->init(lambda, rho);
}

void MuLambdaES::init(unsigned int lambda) {
	if (lambda == 0) throw ValueOutOfRangeException("Lambda parameter must be at least 1.");
	this->lambda = lambda;
	this->rho = 0;
}

void MuLambdaES::init(unsigned int lambda, unsigned int rho) {
	this->init(lambda);
	if (rho < 2) throw ValueOutOfRangeException("Rho parameter must be at least 2.");
	this->rho = rho;
}

std::vector<Genome*> MuLambdaES::getOffspring(
	std::vector<Genome*> parents,
	std::vector<float> parentFitnesses,
	std::string speciesNode
) {
	std::vector<Genome*> offspring;

	for (unsigned int i = 0; i < this->lambda; i++) {
		Genome* result;

		if (this->cross) {
			std::vector<Genome*> crossResults =
				this->cross->crossOver(
					this->strategy->chooseParents(
						parents,
						parentFitnesses,
						this->rho
					),
					speciesNode
				);
			result = new Genome(HierRNG::choose(crossResults));
			for (auto cross: crossResults) delete(cross);
		} else {
			result = new Genome(this->strategy->chooseParents(
				parents,
				parentFitnesses,
				1
			)[0]);
		}

		Genome* mutationResult = this->mutation->mutate(result);
		offspring.push_back(mutationResult);
		delete(result);
	}

	return offspring;
}

MuLambdaES::AdjustableESMutation::AdjustableESMutation() {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
}

MuLambdaES::AdjustableESMutation::AdjustableESMutation(
	double tau,
	double tauPrime
) {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
	this->tau = tau;
	this->tauPrime = tauPrime;
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
