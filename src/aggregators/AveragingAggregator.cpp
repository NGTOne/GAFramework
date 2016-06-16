#include "aggregators/AveragingAggregator.hpp"

int AveragingAggregator::aggregateFitnesses(
	std::vector<int> apportionedFitnesses
) {
	int total = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		total += apportionedFitnesses[i];

	return total/apportionedFitnesses.size();
}
