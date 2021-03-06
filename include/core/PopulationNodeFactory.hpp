#ifndef CORE_PopulationNodeFactory
#define CORE_PopulationNodeFactory

#include "PopulationNode.hpp"

class PopulationNodeFactory {
	private:

	protected:

	public:
	template <typename NodeType, typename... params>
	static PopulationNode * createNode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition*> conditions,
		std::string nodeName,
		params... as
	);

	template <typename NodeType, typename... params>
	static std::vector<PopulationNode *> createNodes(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition*> conditions,
		std::vector<std::string> nodeNames,
		params... as
	);
};

template<typename NodeType, typename... params>
PopulationNode * PopulationNodeFactory::createNode(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	std::vector<EndCondition*> conditions,
	std::string nodeName,
	params... as
) {
	static_assert(
		std::is_base_of<PopulationNode, NodeType>::value,
		"Type provided to population factory is not a population node!"
	);
	return new NodeType(
		populationSize,
		loci,
		objectives,
		populationToString,
		conditions,
		nodeName,
		as...
	);
}

template <typename NodeType, typename... params>
std::vector<PopulationNode *> PopulationNodeFactory::createNodes(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	std::vector<EndCondition*> conditions,
	std::vector<std::string> nodeNames,
	params... as
) {
	std::vector<PopulationNode*> nodes;
	for (unsigned int i = 0; i < nodeNames.size(); i++)
		nodes.push_back(PopulationNodeFactory::createNode<NodeType>(
			populationSize,
			loci,
			objectives,
			populationToString,
			conditions,
			nodeNames[i],
			as...
		));

	return nodes;
}

#endif
