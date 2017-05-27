#ifndef OBJECTIVES_AGGREGATORS_SummingAggregator
#define OBJECTIVES_AGGREGATORS_SummingAggregator

#include "../../core/eval/AggregationFunction.hpp"

class SummingAggregator : public AggregationFunction {
	private:

	protected:
	double aggregateFitnesses(std::vector<double> apportionedFitnesses);

	public:
};

#endif
