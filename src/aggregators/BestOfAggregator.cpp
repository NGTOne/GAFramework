#include "aggregators/BestOfAggregator.hpp"

float BestOfAggregator::aggregateFitnesses(
	std::vector<float> apportionedFitnesses
) {
	float bestFitness = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		if (apportionedFitnesses[i] > bestFitness)
			bestFitness = apportionedFitnesses[i];

	return bestFitness;
}
