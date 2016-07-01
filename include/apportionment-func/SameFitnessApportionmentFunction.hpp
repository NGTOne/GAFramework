#include "../core/ApportionmentFunction.hpp"
#pragma once

class SameFitnessApportionmentFunction : ApportionmentFunction {
	private:

	protected:

	public:
	float apportionFitness(
		Genome * recipient,
		Genome * provider,
		unsigned int recipientPosition,
		float providerFitness
	);
};
