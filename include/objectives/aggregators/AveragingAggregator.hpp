#ifndef OBJECTIVES_AGGREGATORS_AveragingAggregator
#define OBJECTIVES_AGGREGATORS_AveragingAggregator

#include "../../core/eval/AggregationFunction.hpp"

class AveragingAggregator : public AggregationFunction {
	private:

	protected:
	float aggregateFitnesses(std::vector<float> apportionedFitnesses);

	public:
};

#endif
