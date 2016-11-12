#include "loci/delegated/ChooseBestDelegatedLocus.hpp"
#include "loci/delegated/ChooseBestDelegation.hpp"

ChooseBestDelegatedLocus::ChooseBestDelegatedLocus(
	PopulationNode* target
) : DelegatedPopulationLocus(target, new ChooseBestDelegation()) {}
