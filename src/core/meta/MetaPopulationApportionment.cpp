#include "core/meta/MetaPopulationApportionment.hpp"
#include "core/meta/BlanketResolver.hpp"

MetaPopulationApportionment::MetaPopulationApportionment(
	PopulationNode * metaNode,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregation
) : Apportionment(metaNode, apportionment, aggregation) {}

Genome * MetaPopulationApportionment::getOperableGenome(Genome * genome) {
	Genome resolved = BlanketResolver::resolveBlanket(genome);
	return new Genome(&resolved);
}
