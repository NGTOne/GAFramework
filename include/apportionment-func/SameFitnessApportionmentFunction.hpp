#include "../core/ApportionmentFunction.hpp"
#pragma once

class SameFitnessApportionmentFunction : ApportionmentFunction {
	private:

	protected:

	public:
	int apportionFitness(
		Genome * recipient,
		Genome * provider,
		unsigned int recipientPosition,
		int providerFitness
	);
};
