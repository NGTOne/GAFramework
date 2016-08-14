#include "../../core/eval/AggregationFunction.hpp"
#pragma once

class BestOfAggregator : public AggregationFunction {
	private:

	protected:
	float aggregateFitnesses(std::vector<float> apportionedFitnesses);

	public:
};
