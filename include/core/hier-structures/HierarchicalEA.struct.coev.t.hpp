#include "../HierarchicalEA.hpp"
#pragma once

template <typename NodeType, typename... params>
void HierarchicalEA::addCooperativeCoevolution(
	std::vector<ObjectiveFunction*> overallObjectives,
	std::vector<EndCondition*> overallConditions,
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
