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
	if (!this->compareVectorLengths(
		names,
		contextLoci,
		toStrings,
		conditions,
		print,
		end
	)) throw MismatchedCountsException();
	if (!objectives.empty() && objectives.size() != names.size())
		throw MismatchedCountsException();

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

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<std::vector<Locus*>>> contextLoci,
	std::vector<std::vector<std::vector<ObjectiveFunction*>>> objectives,
	std::vector<std::vector<ToStringFunction*>> toStrings,
	std::vector<std::vector<std::vector<EndCondition*>>> conditions,
	std::vector<std::vector<std::string>> names,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	if (!this->compareVectorLengths(
		contextLoci,
		toStrings,
		conditions,
		names,
		print,
		end
	)) throw MismatchedCountsException();
	if (!objectives.empty() && objectives.size() != names.size())
		throw MismatchedCountsException();

	// TODO TODO: Refactor this
	std::vector<Locus*> levelLoci;
	std::vector<PopulationNode*> levelNodes;
	for (unsigned int i = names.size() - 1; i >= 0; i++) {
		if (!this->compareVectorLengths(
			contextLoci[i],
			toStrings[i],
			conditions[i],
			names[i],
			print[i],
			end[i]
		)) throw MismatchedCountsException();
		if (
			!objectives.empty()
			&& objectives[i].size() != names[i].size()
		) throw MismatchedCountsException();

		levelNodes.clear();
		std::vector<Locus*> nodeLoci;
		for (unsigned int k = 0; k < names[i].size(); k++) {
			nodeLoci.clear();
			nodeLoci.insert(
				nodeLoci.end(),
				levelLoci.begin(),
				levelLoci.end()
			);
			nodeLoci.insert(
				nodeLoci.end(),
				contextLoci[i][k].begin(),
				contextLoci[i][k].end()
			);

			levelNodes.push_back(
				PopulationNodeFactory::createNode<NodeType>(
					formula->getPopulationSize(
						nodeLoci.size()
					),
					nodeLoci,
					(!objectives.empty()
						? objectives[i][k]
						: std::vector<
							ObjectiveFunction*
						>({})),
					toStrings[i][k],
					conditions[i][k],
					names[i][k],
					as...
				)
			);
			levelLoci.push_back(
				new PopulationLocus(levelNodes[k])
			);
		}
		this->addNodes(levelNodes, print[i], end[i]);
		levelNodes.clear();
	}

	// Cleanup
	for (unsigned int i = 0; i < levelLoci.size(); i++)
		delete(levelLoci[i]);
}
