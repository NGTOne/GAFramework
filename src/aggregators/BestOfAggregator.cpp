#include "aggregators/BestOfAggregator.hpp"

int BestOfAggregator::aggregateFitnesses(
	std::vector<int> apportionedFitnesses
) {
	int bestFitness = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		if (apportionedFitnesses[i] > bestFitness)
			bestFitness = apportionedFitnesses[i];

	return bestFitness;
}
