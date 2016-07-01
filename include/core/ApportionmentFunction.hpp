#include "Genome.hpp"
#include <vector>
#pragma once

class ApportionmentFunction {
	private:

	protected:

	public:
	virtual ~ApportionmentFunction();

	virtual int apportionFitness(
		Genome * recipient,
		Genome * provider,
		unsigned int recipientStartIndex,
		std::vector<unsigned int> relevantRecipientIndices,
		int providerFitness
	)=0;
};
