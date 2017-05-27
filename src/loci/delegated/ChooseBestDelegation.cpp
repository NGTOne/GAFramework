#include "loci/delegated/ChooseBestDelegation.hpp"
#include <limits>

ChooseBestDelegation::ChooseBestDelegation() {}

ChooseBestDelegation::~ChooseBestDelegation() {}

double ChooseBestDelegation::getBestIndex(PopulationNode* node) {
	std::vector<Fitness> fitnesses = node->getFitnesses();
	Fitness bestFitness = Fitness::lowestPossible();
	unsigned int bestIndex;
	for (unsigned int i = 0; i < fitnesses.size(); i++)
		if (fitnesses[i] > bestFitness) {
			bestIndex = i;
			bestFitness = fitnesses[i];
		}

	return bestIndex;
}
