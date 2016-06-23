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

std::vector<unsigned int> MetaPopulationApportionment::getComponentIndices(
	Genome * upper,
	Genome * target
) {
	unsigned int headIndex = BlanketResolver::findHeadIndex(upper);
	return upper->getIndex<Genome*>(headIndex)
		->getFlattenedIndices(target);
}
