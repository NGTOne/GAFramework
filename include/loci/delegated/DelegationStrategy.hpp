#ifndef LOCI_DELEGATED_DelegationStrategy
#define LOCI_DELEGATED_DelegationStrategy

#include "../../core/EABehaviourObject.hpp"
#include "../../core/PopulationNode.hpp"

class DelegationStrategy: public EABehaviourObject {
	private:

	protected:

	public:
	DelegationStrategy() {};
	virtual ~DelegationStrategy() {};

	virtual double getBestIndex(PopulationNode* node)=0;
};

#endif
