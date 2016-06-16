#include "aggregators/SummingAggregator.hpp"

int SummingAggregator::aggregateFitnesses(
	std::vector<int> apportionedFitnesses
) {
	int total = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		total += apportionedFitnesses[i];

	return total;
}
