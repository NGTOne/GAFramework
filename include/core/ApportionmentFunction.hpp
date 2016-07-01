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
		unsigned int recipientLocation,
		std::vector<unsigned int> recipientIndices,
		int providerFitness
	)=0;
};
