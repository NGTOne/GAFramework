#include "../core/Apportionment.hpp"
#pragma once

class AveragingApportionment : public Apportionment {
	private:

	protected:
	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
	AveragingApportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * func
	);
};
