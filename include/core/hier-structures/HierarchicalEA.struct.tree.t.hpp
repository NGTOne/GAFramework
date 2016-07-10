#include "../HierarchicalEA.hpp"
#include "../../exception/MismatchedCountsException.hpp"
#include "../../exception/ValueOutOfRangeException.hpp"

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
	ObjectiveFunction * globalObjective,
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
			std::vector<ObjectiveFunction*>(1, globalObjective)
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

	this->addConstructiveTree<NodeType>(
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
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<ObjectiveFunction*> topObjectives,
	std::vector<std::vector<ApportionmentFunction*>> apportionments,
	std::vector<std::vector<AggregationFunction*>> aggregators,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	TreeBuilder treeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	std::vector<unsigned int> counts = treeSpec.getLevelSizes();

	this->addConstructiveTree<NodeType>(
		formula,
		this->wrapForPass(contextLoci, counts),
		topObjectives,
		this->wrapForPass(apportionments, counts, 1),
		this->wrapForPass(aggregators, counts, 1),
		this->getNestedEmptyVector<unsigned int>(counts, 1),
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
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<ObjectiveFunction *> topObjectives,
	std::vector<std::vector<ApportionmentFunction*>> apportionments,
	std::vector<std::vector<AggregationFunction*>> aggregators,
	std::vector<std::vector<unsigned int>> tryOns,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	TreeBuilder treeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	std::vector<unsigned int> counts = treeSpec.getLevelSizes();

	this->addConstructiveTree<NodeType>(
		formula,
		this->wrapForPass(contextLoci, counts),
		topObjectives,
		this->wrapForPass(apportionments, counts, 1),
		this->wrapForPass(aggregators, counts, 1),
		this->wrapForPass(tryOns, counts, 1),
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
	std::vector<unsigned int> counts = treeSpec.getLevelSizes();

	this->addConstructiveTree<NodeType>(
		formula,
		contextLoci,
		objectives,
		this->getNestedEmptyVector<ApportionmentFunction*>(counts, 1),
		this->getNestedEmptyVector<AggregationFunction*>(counts, 1),
		this->getNestedEmptyVector<unsigned int>(counts, 1),
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
	std::vector<std::vector<std::vector<Locus*>>> contextLoci,
	std::vector<ObjectiveFunction *> topObjectives,
	std::vector<std::vector<std::vector<ApportionmentFunction*>>>
		apportionments,
	std::vector<std::vector<std::vector<AggregationFunction*>>>
		aggregators,
	std::vector<std::vector<std::vector<unsigned int>>> tryOns,
	std::vector<std::vector<ToStringFunction*>> toStrings,
	std::vector<std::vector<std::vector<EndCondition*>>> conditions,
	TreeBuilder treeSpec,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	std::vector<std::vector<
		std::vector<ObjectiveFunction*>
	>> objectives =	this->getNestedEmptyVector<ObjectiveFunction*>(
		treeSpec.getLevelSizes()
	);

	objectives[0] = {topObjectives};

	this->addConstructiveTree<NodeType>(
		formula,
		contextLoci,
		objectives,
		apportionments,
		aggregators,
		tryOns,
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
	std::vector<std::vector<std::vector<Locus*>>> contextLoci,
	std::vector<std::vector<std::vector<ObjectiveFunction*>>> objectives,
	std::vector<std::vector<std::vector<ApportionmentFunction*>>>
		apportionments,
	std::vector<std::vector<std::vector<AggregationFunction*>>>
		aggregators,
	std::vector<std::vector<std::vector<unsigned int>>> tryOns,
	std::vector<std::vector<ToStringFunction*>> toStrings,
	std::vector<std::vector<std::vector<EndCondition*>>> conditions,
	TreeBuilder treeSpec,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	if (treeSpec.numLevels() < 2) throw ValueOutOfRangeException();
	if (
		!this->compareVectorLengths(contextLoci, objectives, toStrings,
			conditions, print, end, treeSpec.getLevelSizes())
		|| !this->compareVectorLengths(
			apportionments,
			aggregators,
			tryOns
		)
		|| apportionments.size() != treeSpec.numLevels() - 1
	) throw MismatchedCountsException();

	std::vector<PopulationNode*> previousLevelNodes, currentLevelNodes;
	std::vector<Locus*> nodeLoci;
	for (
		unsigned int i = treeSpec.numLevels() - 1;
		i >= 0 && i < treeSpec.numLevels(); // Counteracts wrap-around
		i--
	) {
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
					formula->getPopulationSize(nodeLoci),
					nodeLoci,
					objectives[i][k],
					toStrings[i][k],
					conditions[i][k],
					names[k],
					1,
					as...
				)
			);
		}

		if (!previousLevelNodes.empty())
			this->addApportionments(
				currentLevelNodes,
				previousLevelNodes,
				counts,
				apportionments[i],
				aggregators[i],
				tryOns[i]
			);

		this->addNodes(currentLevelNodes, print[i], end[i]);
		previousLevelNodes = currentLevelNodes;
		currentLevelNodes.clear();
	}
	delete(formula); // TODO: Find a better way to deal with this
}
