#include "Genome.hpp"
#include <vector>
#pragma once

class ApportionmentFunction {
	private:

	protected:

	public:
	virtual ~ApportionmentFunction();

	virtual float apportionFitness(
		Genome * recipient,
		Genome * provider,
		unsigned int recipientStartIndex,
		std::vector<unsigned int> relevantRecipientIndices,
		float providerFitness
	)=0;
};
