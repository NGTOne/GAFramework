#ifndef OBJECTIVES_AGGREGATORS_BestOfAggregator
#define OBJECTIVES_AGGREGATORS_BestOfAggregator

#include "../../core/eval/AggregationFunction.hpp"

class BestOfAggregator : public AggregationFunction {
	private:

	protected:
	double aggregateFitnesses(std::vector<double> apportionedFitnesses);

	public:
};

#endif
