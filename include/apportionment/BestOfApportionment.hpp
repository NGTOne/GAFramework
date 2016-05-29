#include "../core/Apportionment.hpp"
#pragma once

class BestOfApportionment : public Apportionment {
	private:

	protected:
	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
	BestOfApportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * func
	);
};
