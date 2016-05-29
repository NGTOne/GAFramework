#include "ObjectiveFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "PopulationNode.hpp"
#pragma once

// TODO: Work in "trying on" to solve the valley of the dinosaurs
class Apportionment : public ObjectiveFunction {
	private:

	protected:
	ApportionmentFunction * func;
	PopulationNode * upperNode;

	virtual int aggregateFitnesses(vector<int> apportionedFitnesses)=0;

	public:
	Apportionment(PopulationNode * upperNode, ApportionmentFunction * func);

	int checkFitness(Genome * genome);
};
