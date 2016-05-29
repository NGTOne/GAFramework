#include "Genome.hpp"
#pragma once

class ApportionmentFunction {
	private:

	protected:

	public:
	virtual int apportionFitness(
		Genome * recipient,
		Genome * provider,
		int providerFitness
	)=0;
};
