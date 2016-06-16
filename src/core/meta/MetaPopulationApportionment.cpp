#include "core/meta/MetaPopulationApportionment.hpp"

MetaPopulationApportionment::MetaPopulationApportionment(
	PopulationNode * metaNode,
	ApportionmentFunction * func
) : Apportionment(metaNode, func) {}
