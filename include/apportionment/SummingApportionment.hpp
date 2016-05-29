#include "../core/Apportionment.hpp"
#pragma once

class SummingApportionment : public Apportionment {
	private:

	protected:
	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
	SummingApportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * func
	);
};
