#include "../HierarchicalEA.hpp"
#include "../../nodes/NonOptimizingNode.hpp"
#pragma once

#define OVERALL_COEV_NAME "Overall Coevolution"

template <typename NodeType, typename... params>
void HierarchicalEA::addCooperativeCoevolution(
	std::vector<ObjectiveFunction*> overallObjectives,
	std::vector<EndCondition*> overallConditions,
	ToStringFunction * overallToString,
	unsigned int numThreads,
	unsigned int populationSize,
	std::vector<Locus*> loci,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregator,
	ToStringFunction * toString,
	std::vector<EndCondition*> conditions,
	std::vector<std::string> nodeNames,
	bool print,
	bool end,
	params... as
) {
	unsigned int count = nodeNames.size();

	this->addCooperativeCoevolution<NodeType>(
		overallObjectives,
		overallConditions,
		overallToString,
		numThreads,
		this->wrapForPass(populationSize, count),
		this->wrapForPass(loci, count),
		this->wrapForPass(apportionment, count),
		this->wrapForPass(aggregator, count),
		this->wrapForPass(toString, count),
		this->wrapForPass(conditions, count),
		nodeNames,
		this->wrapForPass(print, count),
		this->wrapForPass(end, count),
		as...
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addCooperativeCoevolution(
	std::vector<ObjectiveFunction*> overallObjectives,
	std::vector<EndCondition*> overallConditions,
	ToStringFunction * overallToString,
	unsigned int numThreads,
	std::vector<unsigned int> populationSizes,
	std::vector<std::vector<Locus*>> loci,
	std::vector<ApportionmentFunction*> apportionments,
	std::vector<AggregationFunction*> aggregators,
	std::vector<ToStringFunction*> toStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	std::vector<std::string> nodeNames,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	if (!this->compareVectorLengths(
		populationSizes, loci, apportionments, aggregators, toStrings,
		conditions, nodeNames, print, end
	)) throw MismatchedCountsException();

	for (unsigned int i = 0; i < nodeNames.size(); i++)
		this->addNode(
			PopulationNodeFactory::createNode<NodeType>(
				populationSizes[i],
				loci[i],
				{},
				toStrings[i],
				conditions[i],
				nodeNames[i],
				as...
			),
			print[i],
			end[i]
		);

	std::vector<Locus*> overallLoci;
	for (unsigned int i = 0; i < nodeNames.size(); i++)
		overallLoci.push_back(
			new PopulationLocus(this->getNodeByName(nodeNames[i]))
		);

	this->addNode(
		PopulationNodeFactory::createNode<NonOptimizingNode>(
			numThreads,
			overallLoci,
			overallObjectives,
			overallToString,
			overallConditions,
			OVERALL_COEV_NAME
		),
		true,
		overallConditions.empty()
	);

	for (unsigned int i = 0; i < apportionments.size(); i++)
		this->getNodeByName(nodeNames[i])->addObjective(
			new Apportionment(
				this->getNodeByName(OVERALL_COEV_NAME),
				apportionments[i],
				aggregators[i],
				1
			)
		);
}

template <typename MetaNodeType, typename... params>
void HierarchicalEA::addCooperativeCoevMetaNode(
	std::vector<std::string> coopNodes,
	unsigned int numThreads,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction * toString,
	std::vector<EndCondition*> conditions,
	std::string metaNodeName,
	params... as
) {
	PopulationNode * coevRoot = this->findCoevRootNode(coopNodes);
}
