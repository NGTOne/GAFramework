#include "apportionment/SummingApportionment.hpp"

SummingApportionment::SummingApportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * func
) : Apportionment(upperNode, func) {}

int SummingApportionment::aggregateFitnesses(
	std::vector<int> apportionedFitnesses
) {
	int total = 0;
	for (int i = 0; i < apportionedFitnesses.size(); i++)
		total += apportionedFitnesses[i];

	return total;
}
