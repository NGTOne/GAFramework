#ifndef CORE_META_MetaPopulationFactory
#define CORE_META_MetaPopulationFactory

#include "../PopulationNode.hpp"
#include "../PopulationNodeFactory.hpp"
#include "../eval/Apportionment.hpp"
#include "../eval/ObjectiveFunction.hpp"
#include "../eval/ToStringFunction.hpp"
#include "../../exception/InvalidBlanketException.hpp"
#include "MetaPopulationObjective.hpp"
#include "MetaPopulationToString.hpp"
#include <vector>
#include <tuple>

class MetaPopulationFactory {
	private:

	protected:
	static std::vector<PopulationNode*> getAllHierarchicalNodes(
		std::vector<PopulationNode*> nodes
	);

	static bool isCompleteBlanket(std::vector<PopulationNode*> nodes);
	static bool isValidBlanket(
		std::vector<std::tuple<
			PopulationNode *,
			ApportionmentFunction *,
			AggregationFunction *
		>> nodes
	);

	static std::vector<Locus*> createLoci(
		std::vector<std::tuple<
			PopulationNode *,
			ApportionmentFunction *,
			AggregationFunction *
		>> nodes
	);

	static void addMetaApportionments(
		PopulationNode * metaNode,
		std::vector<std::tuple<
			PopulationNode *,
			ApportionmentFunction *,
			AggregationFunction *
		>> nodes,
		bool clobberExistingObjectives
	);

	public:
	template<typename MetaNodeType, typename... params>
	static PopulationNode * createMeta(
		bool clobberExistingObjectives,
		unsigned int populationSize,
		std::vector<std::tuple<
			PopulationNode *,
			ApportionmentFunction *,
			AggregationFunction *
		>> nodes,
		std::vector<ObjectiveFunction *> flattenedObjectives,
		ToStringFunction * flattenedToString,
		std::vector<EndCondition*> conditions,
		std::string metaNodeName,
		params... as
	);
};

template<typename MetaNodeType, typename... params>
PopulationNode * MetaPopulationFactory::createMeta(
	bool clobberExistingObjectives,
	unsigned int populationSize,
	std::vector<std::tuple<
		PopulationNode *,
		ApportionmentFunction *,
		AggregationFunction *
	>> nodes,
	std::vector<ObjectiveFunction *> flattenedObjectives,
	ToStringFunction * flattenedToString,
	std::vector<EndCondition*> conditions,
	std::string metaNodeName,
	params... as
) {
	if (!MetaPopulationFactory::isValidBlanket(nodes))
		throw InvalidBlanketException();
	std::vector<Locus*> loci = MetaPopulationFactory::createLoci(nodes);

	std::vector<ObjectiveFunction*> metaObjectives;
	for (unsigned int i = 0; i < flattenedObjectives.size(); i++)
		metaObjectives.push_back(
			new MetaPopulationObjective(flattenedObjectives[i])
		);

	PopulationNode * metaNode = PopulationNodeFactory::createNode<
		MetaNodeType
	>(
		populationSize,
		loci,
		metaObjectives,
		new MetaPopulationToString(flattenedToString),
		conditions,
		metaNodeName,
		as...
	);

	MetaPopulationFactory::addMetaApportionments(
		metaNode,
		nodes,
		clobberExistingObjectives
	);
	return metaNode;
}

#endif
