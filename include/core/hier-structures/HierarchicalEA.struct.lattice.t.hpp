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
		std::vector<std::vector<ObjectiveFunction*>>(
			names.size(),
			std::vector<ObjectiveFunction*>()
		),
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
	ObjectiveFunction * globalObjective,
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
		std::vector<std::vector<ObjectiveFunction*>>(
			names.size(),
			std::vector<ObjectiveFunction*>(1, globalObjective)
		),
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
	std::vector<unsigned int> counts;
	for (unsigned int i = 0; i < names.size(); i++)
		counts.push_back(names[i].size());

	this->addConstructiveLattice<NodeType>(
		formula,
		this->wrapForPass(contextLoci, counts),
		this->wrapForPass(objectives, counts),
		this->wrapForPass(toStrings, counts),
		this->wrapForPass(conditions, counts),
		names,
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
	std::vector<std::vector<std::string>> names,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	std::vector<unsigned int> counts;
	for (unsigned int i = 1; i < names.size(); i++)
		counts.push_back(names[i].size());

	this->addConstructiveLattice<NodeType>(
		formula,
		contextLoci,
		objectives,
		this->getNestedEmptyVector<ApportionmentFunction*>(counts),
		this->getNestedEmptyVector<AggregationFunction*>(counts),
		this->getNestedEmptyVector<unsigned int>(counts),
		toStrings,
		conditions,
		names,
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
	std::vector<std::vector<std::string>> names,
	std::vector<std::vector<bool>> print,
	std::vector<std::vector<bool>> end,
	params... as
) {
	if (
		!this->compareVectorLengths(contextLoci, objectives, toStrings,
			conditions, names, print, end)
		|| !this->compareVectorLengths(apportionments, aggregators,
			tryOns)
		|| apportionments.size() != names.size() - 1
	) throw MismatchedCountsException();

	// TODO TODO: Refactor this
	std::vector<Locus*> levelLoci;
	std::vector<PopulationNode*> currentLevelNodes, previousLevelNodes;
	for (
		unsigned int i = names.size() - 1;
		i >= 0 && i < names.size(); // Counteracts unsigned overflow
		i--
	) {
		levelLoci.clear();
		if (!this->compareVectorLengths(
			contextLoci[i],
			objectives[i],
			toStrings[i],
			conditions[i],
			names[i],
			print[i],
			end[i]
		)) throw MismatchedCountsException();

		for (unsigned int k = 0; k < previousLevelNodes.size(); k++)
			levelLoci.push_back(new PopulationLocus(
				previousLevelNodes[k]
			));

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

			currentLevelNodes.push_back(
				PopulationNodeFactory::createNode<NodeType>(
					formula->getPopulationSize(nodeLoci),
					nodeLoci,
					objectives[i][k],
					toStrings[i][k],
					conditions[i][k],
					names[i][k],
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

	delete(formula); // TODO: Find a better way to deal with this
}
