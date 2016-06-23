#include "ObjectiveFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "AggregationFunction.hpp"
#include "PopulationNode.hpp"
#pragma once

class Apportionment : public ObjectiveFunction {
	private:

	protected:
	ApportionmentFunction * apportionment;
	AggregationFunction * aggregator;
	PopulationNode * upperNode;
	unsigned int tryOns;

	void init(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregator,
		unsigned int tryOns
	);

	int aggregateFitnesses(std::vector<int> apportionedFitnesses);
	virtual Genome * getOperableGenome(Genome * genome);
	virtual std::vector<unsigned int> getComponentIndices(
		Genome * upper,
		Genome * target
	);

	void evaluatePair(
		Genome * upper,
		Genome * target,
		int upperFitness,
		std::vector<int> & apportionedFitnesses
	);

	public:
	Apportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregator
	);
	Apportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregator,
		unsigned int tryOns
	);

	virtual ~Apportionment();

	int checkFitness(Genome * genome);

	bool isApportioning();
	ApportionmentFunction * getApportionmentFunction();
	AggregationFunction * getAggregationFunction();
};
