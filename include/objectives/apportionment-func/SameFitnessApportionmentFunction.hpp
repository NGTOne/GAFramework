#include "../../core/eval/ApportionmentFunction.hpp"
#pragma once

class SameFitnessApportionmentFunction : public ApportionmentFunction {
	private:

	protected:

	public:
	float apportionFitness(
		Genome * recipient,
		Genome * provider,
		unsigned int recipientStartIndex,
		std::vector<unsigned int> relevantRecipientIndices,
		float providerFitness
	);
};
