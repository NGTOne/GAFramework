#include "ObjectiveFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "AggregationFunction.hpp"
#include "PopulationNode.hpp"
#pragma once

// TODO: Work in "trying on" to solve the valley of the dinosaurs
class Apportionment : public ObjectiveFunction {
	private:

	protected:
	ApportionmentFunction * apportionment;
	AggregationFunction * aggregator;
	PopulationNode * upperNode;

	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
	Apportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregator
	);
	virtual ~Apportionment();

	int checkFitness(Genome * genome);

	bool isApportioning();
	ApportionmentFunction * getApportionmentFunction();
	AggregationFunction * getAggregationFunction();
};
