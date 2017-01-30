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
	Genome* upper,
	Genome* target
) {
	Genome* head = upper->getIndex<Genome*>(
		BlanketResolver::findHeadIndex(upper)
	);

	if (head == target) {
		// The graph's root node is, by definition, located at index 0
		return std::vector<unsigned int>{0};
	} else {
		std::vector<unsigned int> rawIndices =
			head->getFlattenedSpeciesIndices(target);
		std::vector<unsigned int> indexIndices =
			BlanketResolver::getIndices(upper, target);
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < indexIndices.size(); i++)
			indices.push_back(rawIndices[indexIndices[i]]);
		return indices;
	}
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
			indices.push_back(targetIndex + currentIndex++);
		} else {
			currentIndex += target->getIndex<Genome*>(i)
				->flattenedGenomeLength();
		}

	return indices;
}

bool MetaPopulationApportionment::upperGenomeUsesComponent(
	Genome * upper,
	Genome * target
) {
	for (unsigned int i = 0; i < upper->genomeLength(); i++)
		if (upper->getIndex<Genome*>(i) == target)
			return true;

	return false;
}
