#include "../core/AggregationFunction.hpp"
#pragma once

class BestOfAggregator : public AggregationFunction {
	private:

	protected:
	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
};
