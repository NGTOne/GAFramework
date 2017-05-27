#include "core/meta/MetaPopulationFactory.hpp"
#include "core/PopulationNode.hpp"
#include "core/eval/Apportionment.hpp"
#include "core/eval/ObjectiveFunction.hpp"
#include "core/meta/MetaPopulationObjective.hpp"
#include "core/meta/MetaPopulationApportionment.hpp"
#include "core/meta/MetaPopulationToString.hpp"
#include "loci/PopulationLocus.hpp"

#include <set>

std::vector<PopulationNode*> MetaPopulationFactory::getAllHierarchicalNodes(
	std::vector<PopulationNode*> nodes
) {
	std::set<Locus*> constructiveLoci;
	std::vector<PopulationNode*> unmatchedNodes;
	for (unsigned int i = 0; i < nodes.size(); i++) {
		constructiveLoci = nodes[i]->getConstructiveLoci();
		for (auto k : constructiveLoci)
			unmatchedNodes.push_back(
				((PopulationLocus*)k)->getNode()
			);
	}

	return unmatchedNodes;
}

bool MetaPopulationFactory::isCompleteBlanket(
	std::vector<PopulationNode*> nodes
) {
	std::vector<PopulationNode*> unmatchedNodes =
		MetaPopulationFactory::getAllHierarchicalNodes(nodes);

	unsigned int i = 0, k = 0;
	bool matched;
	while (i < nodes.size()) {
		matched = false;
		while (k < unmatchedNodes.size() && !unmatchedNodes.empty()) {
			if (unmatchedNodes[k] == nodes[i]) {
				unmatchedNodes.erase(
					unmatchedNodes.begin() + k
				);
				nodes.erase(nodes.begin() + i);
				i = k = 0;
				matched = true;
			} else {
				k++;
			}
		}
		k = 0;
		if (!matched) i++;
	}

	// Implies that we only have one root node
	return unmatchedNodes.empty() && nodes.size() == 1;
}

bool MetaPopulationFactory::isValidBlanket(
	std::vector<std::tuple<
		PopulationNode*,
		ApportionmentFunction *
	>> nodes
) {
	std::vector<PopulationNode*> actualNodes;
	for (unsigned int i = 0; i < nodes.size(); i++)
		actualNodes.push_back(std::get<0>(nodes[i]));

	if (!MetaPopulationFactory::isCompleteBlanket(actualNodes))
		return false;
	return true;
}

std::vector<Locus*> MetaPopulationFactory::createLoci(
	std::vector<std::tuple<
		PopulationNode*,
		ApportionmentFunction *
	>> nodes
) {
	std::vector<Locus*> loci;
	for (unsigned int i = 0; i < nodes.size(); i++)
		loci.push_back(new PopulationLocus(std::get<0>(nodes[i])));

	return loci;
}

void MetaPopulationFactory::addMetaApportionments(
	PopulationNode * metaNode,
	std::vector<std::tuple<
		PopulationNode*,
		ApportionmentFunction *
	>> nodes,
	bool clobberExistingObjectives
) {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		if (std::get<1>(nodes[i]) == NULL) continue;

		ObjectiveFunction * apportion =
			new MetaPopulationApportionment(
				metaNode,
				std::get<1>(nodes[i])
			);

		if (clobberExistingObjectives) {
			std::get<0>(nodes[i])->setObjective(apportion);
		} else {
			std::get<0>(nodes[i])->addObjective(apportion);
		}
	}
}
