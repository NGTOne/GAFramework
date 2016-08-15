#ifndef CORE_EVAL_ApportionmentFunction
#define CORE_EVAL_ApportionmentFunction

#include "../Genome.hpp"
#include "../EABehaviourObject.hpp"
#include <vector>

class ApportionmentFunction : public EABehaviourObject {
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

#endif
