#ifndef OBJECTIVES_AGGREGATORS_AveragingAggregator
#define OBJECTIVES_AGGREGATORS_AveragingAggregator

#include "../../core/eval/AggregationFunction.hpp"

class AveragingAggregator : public AggregationFunction {
	private:

	protected:
	double aggregateFitnesses(std::vector<double> apportionedFitnesses);

	public:
};

#endif
