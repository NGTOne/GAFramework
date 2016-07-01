#include "../core/AggregationFunction.hpp"
#pragma once

class SummingAggregator : public AggregationFunction {
	private:

	protected:
	float aggregateFitnesses(std::vector<float> apportionedFitnesses);

	public:
};
