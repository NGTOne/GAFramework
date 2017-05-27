#ifndef CORE_EVAL_ApportionmentFunction
#define CORE_EVAL_ApportionmentFunction

#include "core/Genome.hpp"
#include "core/EABehaviourObject.hpp"
#include "core/Fitness.hpp"
#include <vector>

class ApportionmentFunction : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~ApportionmentFunction();

	virtual float apportionFitness(
		Genome* recipient,
		Genome* provider,
		unsigned int recipientStartIndex,
		std::vector<unsigned int> relevantRecipientIndices,
		Fitness providerFitness
	)=0;
};

#endif
