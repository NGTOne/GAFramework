#include "nodes/EANode/systems/ES/MuCommaLambdaES.hpp"

MuCommaLambdaES::MuCommaLambdaES(
	MutationOperation* mutation,
	unsigned int lambda
) : MuLambdaES(mutation, lambda) {}

MuCommaLambdaES::MuCommaLambdaES(
	MutationOperation* mutation,
	SelectionStrategy* selection,
	unsigned int lambda
) : MuLambdaES(mutation, lambda) {}

MuCommaLambdaES::MuCommaLambdaES(
	CrossoverOperation* cross,
	MutationOperation* mutation,
	unsigned int lambda,
	unsigned int rho
) : MuLambdaES(cross, mutation, lambda, rho) {}

MuCommaLambdaES::MuCommaLambdaES(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation,
	unsigned int lambda,
	unsigned int rho
) : MuLambdaES(strategy, cross, mutation, lambda, rho) {}

std::vector<Genome*> MuCommaLambdaES::doReplacement(
	std::vector<Genome*> parents,
	std::vector<Genome*> offspring,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives
) {
	std::vector<Genome*> result;
	std::vector<float> offspringFitnesses;

	for (unsigned int i = 0; i < offspring.size(); i++)
		offspringFitnesses.push_back(this->evaluateFitness(
			offspring[i],
			objectives
		));
	this->sortPopulation(offspring, offspringFitnesses);

	for (unsigned int i = 0; i < parents.size(); i++) {
		result.push_back(offspring[i]);
		populationFitnesses[i] = offspringFitnesses[i];
	}

	return result;
}
