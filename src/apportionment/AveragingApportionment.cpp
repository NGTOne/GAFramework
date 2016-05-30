#include "apportionment/AveragingApportionment.hpp"

AveragingApportionment::AveragingApportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * func
) : Apportionment(upperNode, func) {}

int AveragingApportionment::aggregateFitnesses(
	std::vector<int> apportionedFitnesses
) {
	int total = 0;
	for (unsigned int i = 0; i < apportionedFitnesses.size(); i++)
		total += apportionedFitnesses[i];

	return total/apportionedFitnesses.size();
}
