#include "../core/AggregationFunction.hpp"
#pragma once

class SummingAggregator : public AggregationFunction {
	private:

	protected:
	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
};
