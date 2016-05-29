#include "apportionment/BestOfApportionment.hpp"

BestOfApportionment::BestOfApportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * func
) : Apportionment(upperNode, func) {}

int BestOfApportionment::aggregateFitnesses(
	std::vector<int> apportionedFitnesses
) {
	int bestFitness = 0;
	for (int i = 0; i < apportionedFitnesses.size(); i++)
		if (apportionedFitnesses[i] > bestFitness)
			bestFitness = apportionedFitnesses[i];

	return bestFitness;
}
