#include "../HierarchicalEA.hpp"

template <typename Node, typename... params>
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
			std::vector<ObjectiveFunction*>
		),
		toStrings,
		conditions,
		treeSpec,
		print,
		end,
		as...
	);
}

template <typename Node, typename... params>
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
