#include "../HierarchicalEA.hpp"
#include "../../exception/MismatchedCountsException.hpp"

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveTree(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	TreeBuilder treeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	this->addConstructiveTree<NodeType>(
		formula,
		contextLoci,
		std::vector<std::vector<ObjectiveFunction*>>(
			treeSpec.numLevels(),
			std::vector<ObjectiveFunction*>()
		),
		toStrings,
		conditions,
		treeSpec,
		print,
		end,
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveTree(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<std::vector<ObjectiveFunction*>> objectives,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	TreeBuilder treeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	std::vector<unsigned int> counts = treeSpec.getLevelSizes();

	this->addConstructiveLattice<NodeType>(
		formula,
		this->wrapForPass(contextLoci, counts),
		this->wrapForPass(objectives, counts),
		this->wrapForPass(toStrings, counts),
		this->wrapForPass(conditions, counts),
		treeSpec,
		this->wrapForPass(print, counts),
		this->wrapForPass(end, counts),
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveTree(
	PopulationFormula * formula,
	std::vector<std::vector<std::vector<Locus*>>> contextLoci,
	std::vector<std::vector<std::vector<ObjectiveFunction*>>> objectives,
	std::vector<std::vector<ToStringFunction*>> toStrings,
	std::vector<std::vector<std::vector<EndCondition*>>> conditions,
	TreeBuilder treeSpec,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	if (!this->compareVectorLengths(
		contextLoci,
		objectives,
		toStrings,
		conditions,
		print,
		end,
		treeSpec.getLevelSizes()
	)) throw MismatchedCountsException();

	std::vector<PopulationNode*> previousLevelNodes, currentLevelNodes;
	std::vector<Locus*> nodeLoci;
	for (unsigned int i = treeSpec.numLevels() - 1; i >= 0; i++) {
		std::vector<std::string> names = treeSpec.getLevel(i);
		std::vector<unsigned int> counts = treeSpec.getLevelCounts(i);
		unsigned int currentOffset = 0;

		if (!this->compareVectorLengths(
			contextLoci[i],
			objectives[i],
			toStrings[i],
			conditions[i],
			names,
			print[i],
			end[i]
		)) throw MismatchedCountsException();

		for (unsigned int k = 0; k < names.size(); k++) {
			nodeLoci.clear();
			for (unsigned int c = 0; c < counts[k]; c++)
				nodeLoci.push_back(new PopulationLocus(
					previousLevelNodes[currentOffset++]
				));
			nodeLoci.insert(
				nodeLoci.end(),
				contextLoci[i][k].begin(),
				contextLoci[i][k].end()
			);

			currentLevelNodes.push_back(
				PopulationNodeFactory::createNode<NodeType>(
					formula->getPopulationSize(
						nodeLoci.size()
					),
					nodeLoci,
					objectives[i][k],
					toStrings[i][k],
					conditions[i][k],
					names[i][k],
					as...
				)
			);
		}
		this->addNodes(currentLevelNodes, print[i], end[i]);
		previousLevelNodes = currentLevelNodes;
		currentLevelNodes.clear();
	}
}
