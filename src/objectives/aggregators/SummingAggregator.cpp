#include "objectives/aggregators/SummingAggregator.hpp"

double SummingAggregator::aggregateFitnesses(
	std::vector<double> apportionedFitnesses
) {
	double total = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		total += apportionedFitnesses[i];

	return total;
}
