#include "core/meta/MetaPopulationApportionment.hpp"

MetaPopulationApportionment::MetaPopulationApportionment(
	PopulationNode * metaNode,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregation
) : Apportionment(metaNode, apportionment, aggregation) {}
