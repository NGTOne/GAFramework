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
	Genome * head = upper->getIndex<Genome*>(
		BlanketResolver::findHeadIndex(upper)
	);

	return (head == target) ?
		std::vector<unsigned int>(1, 0) :
		head->getFlattenedSpeciesIndices(target);
}

std::vector<unsigned int> MetaPopulationApportionment::getRelevantIndices(
	Genome * target,
	unsigned int targetIndex
) {
	std::vector<Locus*> targetLoci = target->getLoci();
	std::vector<unsigned int> indices;
	unsigned int currentIndex = 0;

	for (unsigned int i = 0; i < targetLoci.size(); i++)
		if (!targetLoci[i]->isConstructive()) {
			indices.push_back(targetIndex + currentIndex);
		} else {
			currentIndex += target->getIndex<Genome*>(i)
				->flattenedGenomeLength();
		}

	return indices;
}
