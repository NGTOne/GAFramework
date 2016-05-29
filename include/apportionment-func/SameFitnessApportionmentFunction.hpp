#include "../core/ApportionmentFunction.hpp"
#pragma once

class SameFitnessApportionmentFunction : ApportionmentFunction {
	private:

	protected:

	public:
	int apportionFitness(
		Genome * recipient,
		Genome * provider,
		int providerFitness
	);
};
