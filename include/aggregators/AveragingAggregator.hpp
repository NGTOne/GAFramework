#include "../core/AggregationFunction.hpp"
#pragma once

class AveragingAggregator : public AggregationFunction {
	private:

	protected:
	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
};
