#include "nodes/EANode/systems/ES/MuCommaLambdaES.hpp"
#include "exception/ValueOutOfRangeException.hpp"

std::vector<Genome*> MuCommaLambdaES::doReplacement(
	std::vector<Genome*> parents,
	std::vector<Genome*> offspring,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives
) {
	if (offspring.size() < parents.size()) throw ValueOutOfRangeException("A (mu, lambda)-ES must have a lambda of at least mu in order to function properly. Increase the lambda parameter.");
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
