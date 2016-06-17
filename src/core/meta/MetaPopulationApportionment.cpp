#include "core/meta/MetaPopulationApportionment.hpp"

MetaPopulationApportionment::MetaPopulationApportionment(
	PopulationNode * metaNode,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregation
) : Apportionment(metaNode, apportionment, aggregation) {}

Genome * MetaPopulationApportionment::getOperableGenome(Genome * genome) {
	Genome resolved = this->resolveBlanket(genome);
	return new Genome(&resolved);
}
