#ifndef LOCI_DELEGATED_DelegatedPopulationLocus
#define LOCI_DELEGATED_DelegatedPopulationLocus

#include "../PopulationLocus.hpp"
#include "DelegationStrategy.hpp"

class DelegatedPopulationLocus: public PopulationLocus {
	private:

	protected:
	DelegationStrategy* strategy;

	public:
	DelegatedPopulationLocus(
		PopulationNode* target,
		DelegationStrategy* strategy
	);

	virtual void registerInternalObjects();

	virtual std::string flatten(Gene* index);
	virtual boost::any getIndex(Gene* index);
};

#endif
