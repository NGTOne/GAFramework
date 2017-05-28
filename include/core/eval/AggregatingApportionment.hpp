#ifndef CORE_EVAL_AggregatingApportionment
#define CORE_EVAL_AggregatingApportionment

#include "AggregationFunction.hpp"
#include "Apportionment.hpp"

class AggregatingApportionment : public Apportionment {
	private:

	protected:
	AggregationFunction* aggregator;
	double aggregateFitnesses(
		std::vector<FitnessPair> apportionedFitnesses
	);
	virtual std::vector<FitnessPair> postProcessFitnesses(
		std::vector<FitnessPair> apportionedFitnesses
	);

	public:
	AggregatingApportionment(
		PopulationNode* upperNode,
		ApportionmentFunction* apportionment,
		AggregationFunction* aggregator
	);
	AggregatingApportionment(
		PopulationNode* upperNode,
		ApportionmentFunction* apportionment,
		AggregationFunction* aggregator,
		unsigned int tryOns
	);

	virtual void registerInternalObjects();
	AggregationFunction* getAggregationFunction();
};

#endif
