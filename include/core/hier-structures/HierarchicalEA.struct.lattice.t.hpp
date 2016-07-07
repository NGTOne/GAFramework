#include "../HierarchicalEA.hpp"
#include "../PopulationNodeFactory.hpp"
#include "../../exception/MismatchedCountsException.hpp"
#pragma once

template<typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	std::vector<std::vector<std::string>> names,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	this->addConstructiveLattice<NodeType>(
		formula,
		contextLoci,
		std::vector<ObjectiveFunction*>({}),
		toStrings,
		conditions,
		names,
		print,
		end,
		as...
	);
}

template<typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<std::vector<ObjectiveFunction*>> objectives,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	std::vector<std::vector<std::string>> names,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	if (
		names.size() != contextLoci.size()
		|| (!objectives.empty() && names.size() != objectives.size())
		|| names.size() != toStrings.size()
		|| names.size() != conditions.size()
		|| names.size() != print.size()
		|| names.size() != end.size()
	) throw MismatchedCountsException(); // TODO: Refactor this

	std::vector<Locus*> levelLoci;
	std::vector<PopulationNode*> levelNodes;
	for (unsigned int i = names.size() - 1; i >= 0; i--) {
		levelLoci.insert(
			levelLoci.end(),
			contextLoci[i].begin(),
			contextLoci[i].end()
		);

		levelNodes = PopulationNodeFactory::createNodes<NodeType>(
			formula->getPopulationSize(levelLoci.size()),
			levelLoci,
			(!objectives.empty() ? objectives[i]
				: std::vector<ObjectiveFunction*>({})),
			toStrings[i],
			conditions[i],
			names[i],
			as...
		);

		this->addNodes(levelNodes, print[i], end[i]);
		levelLoci.clear();
		for (unsigned int k = 0; k < levelNodes.size(); k++)
			levelLoci.push_back(
				new PopulationLocus(levelNodes[k])
			);
	}

	// Clean up - otherwise the "head" nodes will have unused loci
	// pointing to them
	for (unsigned int i = 0; i < levelLoci.size(); i++)
		delete(levelLoci[i]);
}
