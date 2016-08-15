#ifndef OBJECTIVES_APPORTIONMENT_FUNC_SameFitnessApportionmentFunction
#define OBJECTIVES_APPORTIONMENT_FUNC_SameFitnessApportionmentFunction

#include "../../core/eval/ApportionmentFunction.hpp"

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

#endif
