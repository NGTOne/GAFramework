#include "../HierarchicalEA.hpp"
#include "../HierGC.hpp"
#include "../PopulationNodeFactory.hpp"
#include "../../exception/MismatchedCountsException.hpp"
#include "../../loci/PopulationLocus.hpp"
#pragma once

template<typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	LatticeBuilder latticeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	this->addConstructiveLattice<NodeType>(
		formula,
		contextLoci,
		std::vector<std::vector<ObjectiveFunction*>>(
			latticeSpec.numLevels(),
			std::vector<ObjectiveFunction*>()
		),
		toStrings,
		conditions,
		latticeSpec,
		print,
		end,
		as...
	);
}

template<typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	ObjectiveFunction * globalObjective,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	LatticeBuilder latticeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	this->addConstructiveLattice<NodeType>(
		formula,
		contextLoci,
		std::vector<std::vector<ObjectiveFunction*>>(
			latticeSpec.numLevels(),
			std::vector<ObjectiveFunction*>(1, globalObjective)
		),
		toStrings,
		conditions,
		latticeSpec,
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
	LatticeBuilder latticeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	std::vector<unsigned int> counts = latticeSpec.getLevelSizes();

	this->addConstructiveLattice<NodeType>(
		formula,
		this->wrapForPass(contextLoci, counts),
		this->wrapForPass(objectives, counts),
		this->wrapForPass(toStrings, counts),
		this->wrapForPass(conditions, counts),
		latticeSpec,
		this->wrapForPass(print, counts),
		this->wrapForPass(end, counts),
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<ObjectiveFunction*> topObjectives,
	std::vector<std::vector<ApportionmentFunction*>> apportionments,
	std::vector<std::vector<AggregationFunction*>> aggregators,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	LatticeBuilder latticeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	std::vector<unsigned int> counts = latticeSpec.getLevelSizes();

	this->addConstructiveLattice<NodeType>(
		formula,
		this->wrapForPass(contextLoci, counts),
		topObjectives,
		this->wrapForPass(apportionments, counts, 1),
		this->wrapForPass(aggregators, counts, 1),
		this->getNestedEmptyVector<unsigned int>(counts, 1),
		this->wrapForPass(toStrings, counts),
		this->wrapForPass(conditions, counts),
		latticeSpec,
		this->wrapForPass(print, counts),
		this->wrapForPass(end, counts),
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<Locus*>> contextLoci,
	std::vector<ObjectiveFunction *> topObjectives,
	std::vector<std::vector<ApportionmentFunction*>> apportionments,
	std::vector<std::vector<AggregationFunction*>> aggregators,
	std::vector<std::vector<unsigned int>> tryOns,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	LatticeBuilder latticeSpec,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	std::vector<unsigned int> counts = latticeSpec.getLevelSizes();

	this->addConstructiveLattice<NodeType>(
		formula,
		this->wrapForPass(contextLoci, counts),
		topObjectives,
		this->wrapForPass(apportionments, counts, 1),
		this->wrapForPass(aggregators, counts, 1),
		this->wrapForPass(tryOns, counts, 1),
		this->wrapForPass(toStrings, counts),
		this->wrapForPass(conditions, counts),
		latticeSpec,
		this->wrapForPass(print, counts),
		this->wrapForPass(end, counts),
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
	PopulationFormula * formula,
	std::vector<std::vector<std::vector<Locus*>>> contextLoci,
	std::vector<std::vector<std::vector<ObjectiveFunction*>>> objectives,
	std::vector<std::vector<ToStringFunction*>> toStrings,
	std::vector<std::vector<std::vector<EndCondition*>>> conditions,
	LatticeBuilder latticeSpec,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	std::vector<unsigned int> counts = latticeSpec.getLevelSizes();

	this->addConstructiveLattice<NodeType>(
		formula,
		contextLoci,
		objectives,
		this->getNestedEmptyVector<ApportionmentFunction*>(counts, 1),
		this->getNestedEmptyVector<AggregationFunction*>(counts, 1),
		this->getNestedEmptyVector<unsigned int>(counts, 1),
		toStrings,
		conditions,
		latticeSpec,
		print,
		end,
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
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
	LatticeBuilder latticeSpec,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	std::vector<unsigned int> counts = latticeSpec.getLevelSizes();

	std::vector<std::vector<
		std::vector<ObjectiveFunction*>
	>> objectives =	this->getNestedEmptyVector<ObjectiveFunction*>(counts);

	objectives[0] =	std::vector<std::vector<ObjectiveFunction*>>(
		counts[0],
		topObjectives
	);

	this->addConstructiveLattice<NodeType>(
		formula,
		contextLoci,
		objectives,
		apportionments,
		aggregators,
		tryOns,
		toStrings,
		conditions,
		latticeSpec,
		print,
		end,
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addConstructiveLattice(
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
	LatticeBuilder latticeSpec,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	if (
		!this->compareVectorLengths(contextLoci, objectives, toStrings,
			conditions, print, end)
		|| !this->compareVectorLengths(apportionments, aggregators,
			tryOns)
		|| apportionments.size() != latticeSpec.numLevels() - 1
		|| contextLoci.size() != latticeSpec.numLevels()
	) throw MismatchedCountsException();

	// TODO TODO: Refactor this
	std::vector<Locus*> levelLoci;
	std::vector<PopulationNode*> currentLevelNodes, previousLevelNodes;
	for (
		unsigned int i = latticeSpec.numLevels() - 1;
		i < latticeSpec.numLevels(); // Overflow means we're done
		i--
	) {
		levelLoci.clear();
		if (!this->compareVectorLengths(
			contextLoci[i],
			objectives[i],
			toStrings[i],
			conditions[i],
			latticeSpec.getLevel(i),
			print[i],
			end[i]
		)) throw MismatchedCountsException();

		for (unsigned int k = 0; k < previousLevelNodes.size(); k++)
			levelLoci.push_back(new PopulationLocus(
				previousLevelNodes[k]
			));

		std::vector<Locus*> nodeLoci;
		std::vector<std::string> names = latticeSpec.getLevel(i);
		for (unsigned int k = 0; k < names.size(); k++) {
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
				apportionments[i],
				aggregators[i],
				tryOns[i]
			);

		previousLevelNodes = currentLevelNodes;
		this->addNodes(currentLevelNodes, print[i], end[i]);
		currentLevelNodes.clear();
	}

	HierGC::registerObject(formula);
}
