#include "aggregators/AveragingAggregator.hpp"

float AveragingAggregator::aggregateFitnesses(
	std::vector<float> apportionedFitnesses
) {
	float total = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		total += apportionedFitnesses[i];

	return total/apportionedFitnesses.size();
}
