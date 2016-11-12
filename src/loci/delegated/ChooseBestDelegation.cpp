#include "loci/delegated/ChooseBestDelegation.hpp"
#include <limits>

ChooseBestDelegation::ChooseBestDelegation() {}

ChooseBestDelegation::~ChooseBestDelegation() {}

double ChooseBestDelegation::getBestIndex(PopulationNode* node) {
	std::vector<float> fitnesses = node->getFitnesses();
	float bestFitness = std::numeric_limits<float>::lowest();
	unsigned int bestIndex;
	for (unsigned int i = 0; i < fitnesses.size(); i++)
		if (fitnesses[i] > bestFitness) {
			bestIndex = i;
			bestFitness = fitnesses[i];
		}

	return bestIndex;
}
