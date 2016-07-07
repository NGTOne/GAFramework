#include "HierarchicalEA.hpp"
#include "PopulationNodeFactory.hpp"

template<typename NodeType, typename... params>
void HierarchicalEA::addMigratoryRing(
	bool bidirectional,
	unsigned int n,
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction * nodeToString,
	std::vector<EndCondition*> conditions,
	std::vector<std::string> names,
	bool print,
	bool end,
	params... as
) {
	std::vector<
		PopulationNode *
	> nodes = PopulationNodeFactory::createNodes<NodeType>(
		populationSize,
		loci,
		objectives,
		nodeToString,
		conditions,
		names,
		as...
	);

	this->addNodes(nodes, print, end);
	for (unsigned int i = 0; i < names.size() - 1; i++)
		this->addMigratoryRelationship(
			names[i],
			names[i + 1],
			bidirectional,
			n
		);

	this->addMigratoryRelationship(
		names[names.size() - 1],
		names[0],
		bidirectional,
		n
	);
}
