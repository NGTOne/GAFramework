#ifndef CORE_HIER_STRUCTURES_HierarchicalEA_meta_t
#define CORE_HIER_STRUCTURES_HierarchicalEA_meta_t

#include "../HierarchicalEA.hpp"
#include "../meta/MetaPopulationFactory.hpp"

template<typename MetaNodeType, typename... params>
void HierarchicalEA::addMetaPopulation(
	bool clobberExistingObjectives,
	unsigned int populationSize,
	std::tuple<
		std::vector<std::string>,
		ApportionmentFunction*,
		AggregationFunction*
	> nodes,
	std::vector<ObjectiveFunction*> flattenedObjectives,
	ToStringFunction* flattenedToString,
	std::vector<EndCondition*> conditions,
	std::string metaNodeName,
	params... as
) {
	std::vector<std::tuple<
		std::string,
		ApportionmentFunction*,
		AggregationFunction*
	>> fullNodes;
	for (unsigned int i = 0; i < std::get<0>(nodes).size(); i++)
		fullNodes.push_back(std::make_tuple(
			std::get<0>(nodes)[i],
			std::get<1>(nodes),
			std::get<2>(nodes)
		));

	this->addMetaPopulation<MetaNodeType>(
		clobberExistingObjectives,
		populationSize,
		fullNodes,
		flattenedObjectives,
		flattenedToString,
		conditions,
		metaNodeName,
		as...
	);
}

template<typename MetaNodeType, typename... params>
void HierarchicalEA::addMetaPopulation(
	bool clobberExistingObjectives,
	unsigned int populationSize,
	std::vector<std::tuple<
		std::string,
		ApportionmentFunction*,
		AggregationFunction*
	>> nodes,
	std::vector<ObjectiveFunction*> flattenedObjectives,
	ToStringFunction* flattenedToString,
	std::vector<EndCondition*> conditions,
	std::string metaNodeName,
	params... as
) {
	std::vector<std::tuple<
		PopulationNode*,
		ApportionmentFunction*,
		AggregationFunction*
	>> trueNodes;
	for (unsigned int i = 0; i < nodes.size(); i++)
		trueNodes.push_back(std::make_tuple(
			this->getNodeByName(std::get<0>(nodes[i])),
			std::get<1>(nodes[i]),
			std::get<2>(nodes[i])
		));

	this->addNode(
		MetaPopulationFactory::createMeta<MetaNodeType>(
			clobberExistingObjectives,
			populationSize,
			trueNodes,
			flattenedObjectives,
			flattenedToString,
			conditions,
			metaNodeName,
			1,
			as...
		),
		false,
		false
	);
}

#endif
