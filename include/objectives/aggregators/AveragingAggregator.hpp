#include "../../core/eval/AggregationFunction.hpp"
#pragma once

class AveragingAggregator : public AggregationFunction {
	private:

	protected:
	float aggregateFitnesses(std::vector<float> apportionedFitnesses);

	public:
};
