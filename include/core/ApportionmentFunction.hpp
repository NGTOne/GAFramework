#include "Genome.hpp"
#pragma once

class ApportionmentFunction {
	private:

	protected:

	public:
	virtual ~ApportionmentFunction();

	virtual int apportionFitness(
		Genome * recipient,
		Genome * provider,
		unsigned int recipientPosition,
		int providerFitness
	)=0;
};
