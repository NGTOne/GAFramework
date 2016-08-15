#ifndef OBJECTIVES_AGGREGATORS_SummingAggregator
#define OBJECTIVES_AGGREGATORS_SummingAggregator

#include "../../core/eval/AggregationFunction.hpp"

class SummingAggregator : public AggregationFunction {
	private:

	protected:
	float aggregateFitnesses(std::vector<float> apportionedFitnesses);

	public:
};

#endif
