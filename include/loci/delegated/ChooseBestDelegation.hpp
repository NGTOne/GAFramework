#ifndef LOCI_DELEGATED_ChooseBestDelegation
#define LOCI_DELEGATED_ChooseBestDelegation

#include "DelegationStrategy.hpp"

class ChooseBestDelegation: public DelegationStrategy {
	private:

	protected:

	public:
	ChooseBestDelegation();
	~ChooseBestDelegation();

	double getBestIndex(PopulationNode* node);
};

#endif
