#include "objectives/aggregators/BestOfAggregator.hpp"

double BestOfAggregator::aggregateFitnesses(
	std::vector<double> apportionedFitnesses
) {
	double bestFitness = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		if (apportionedFitnesses[i] > bestFitness)
			bestFitness = apportionedFitnesses[i];

	return bestFitness;
}
