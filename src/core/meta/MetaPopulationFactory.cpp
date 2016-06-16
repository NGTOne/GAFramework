#include "core/meta/MetaPopulationFactory.hpp"
#include "core/PopulationNode.hpp"
#include "core/Apportionment.hpp"
#include "core/ObjectiveFunction.hpp"
#include "core/meta/MetaPopulationObjective.hpp"
#include "core/meta/MetaPopulationApportionment.hpp"
#include "core/meta/MetaPopulationToString.hpp"
#include "loci/PopulationLocus.hpp"

#include <set>

// TODO: Refactor this
bool MetaPopulationFactory::isCompleteBlanket(
	std::vector<PopulationNode*> nodes
) {
	std::vector<Locus*> constructiveLoci;
	std::set<Locus*> rawConstructiveLoci;
	std::vector<PopulationNode*> unmatchedNodes;

	for (unsigned int i = 0; i < nodes.size(); i++) {
		rawConstructiveLoci = nodes[i]->getConstructiveLoci();
		constructiveLoci = std::vector<Locus*>(
			rawConstructiveLoci.begin(),
			rawConstructiveLoci.end()
		);
		for (unsigned int k = 0; k < constructiveLoci.size(); k++)
			unmatchedNodes.push_back(
				((PopulationLocus*)constructiveLoci[k])
					->getNode()
			);
	}

	for (unsigned int i = 0; i < nodes.size(); i++) {
		bool present = false;
		for (unsigned int k = 0; k < unmatchedNodes.size(); k++)
			if (unmatchedNodes[k] == nodes[i]) {
				present = true;
				k = unmatchedNodes.size();
			}
		if (!present) return false;
	}

	return true;
}

bool MetaPopulationFactory::isValidBlanket(
	std::vector<PopulationNode*> nodes
) {
	if (!MetaPopulationFactory::isCompleteBlanket(nodes)) return false;
}

PopulationNode * MetaPopulationFactory::createMeta(
	PopulationNode * metaNode,
	std::vector<ObjectiveFunction *> flattenedObjectives,
	ToStringFunction * flattenedToString,
	PopulationNode * topNode,
	Apportionment * topNodeApportionment,
	std::vector<std::tuple<
		PopulationNode *,
		Apportionment *
	>> secondaryNodes
) {
	std::vector<Locus*> newLoci;
	newLoci.push_back(new PopulationLocus(topNode));
	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		newLoci.push_back(new PopulationLocus(
			std::get<0>(secondaryNodes[i])
		));

	metaNode->setLoci(newLoci);

	// The normal varieties won't work on a meta-population anyways
	metaNode->setObjectives({});
	metaNode->setToString(new MetaPopulationToString(flattenedToString));

	for (unsigned int i = 0; i < flattenedObjectives.size(); i++)
		metaNode->addObjective((ObjectiveFunction*)
			new MetaPopulationObjective(flattenedObjectives[i])
		);

	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		std::get<0>(secondaryNodes[i])->addObjective(
			(ObjectiveFunction*)new MetaPopulationApportionment(
				metaNode,
				std::get<1>(secondaryNodes[i])
			)
		);

	return metaNode;
}
