#include "nodes/EANode/systems/ES/MuLambdaES.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "core/utils/HierRNG.hpp"

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

MuLambdaES::AdjustableESMutation::AdjustableESMutation(
	std::vector<unsigned int> stdDevIndices
) {
	this->stdDevIndices = stdDevIndices;
	this->fixedMutations = std::map<unsigned int, MutationOperation*>();
}

MuLambdaES::AdjustableESMutation::AdjustableESMutation(
	std::map<unsigned int, MutationOperation*> fixedMutations,
	std::vector<unsigned int> stdDevIndices
) {
	this->fixedMutations = fixedMutations;
	this->stdDevIndices = stdDevIndices;
}