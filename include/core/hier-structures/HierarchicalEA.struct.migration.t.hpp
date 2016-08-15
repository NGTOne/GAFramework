#ifndef CORE_HIER_STRUCTURES_HierarchicalEA_struct_migration_t
#define CORE_HIER_STRUCTURES_HierarchicalEA_struct_migration_t

#include "../HierarchicalEA.hpp"
#include "../PopulationNodeFactory.hpp"

template<typename NodeType, typename... params>
void HierarchicalEA::addMigratoryRing(
	bool bidirectional,
	unsigned int n,
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* nodeToString,
	std::vector<EndCondition*> conditions,
	std::vector<std::string> names,
	bool print,
	bool end,
	params... as
) {
	std::vector<
		PopulationNode*
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

template<typename NodeType, typename... params>
void HierarchicalEA::addMigratoryTorus(
	bool bidirectionalHorizontal,
	bool bidirectionalVertical,
	unsigned int n,
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* nodeToString,
	std::vector<EndCondition*> conditions,
	std::vector<std::vector<std::string>> names,
	bool print,
	bool end,
	params... as
) {
	for (unsigned int i = 1; i < names.size(); i++)
		if (names[i].size() != names[i-1].size())
			throw MismatchedCountsException();

	for (unsigned int i = 0; i < names.size(); i++)
		this->addMigratoryRing<NodeType>(
			bidirectionalHorizontal,
			n,
			populationSize,
			loci,
			objectives,
			nodeToString,
			conditions,
			names[i],
			print,
			end,
			as...
		);

	for (unsigned int i = 0; i < names.size() - 1; i++)
		for (unsigned int k = 0; k < names[i].size(); k++)
			this->addMigratoryRelationship(
				names[i][k],
				names[i+1][k],
				bidirectionalVertical,
				n
			);

	// Loop around the doughnut hole
	for (unsigned int i = 0; i < names[names.size() - 1].size(); i++)
		this->addMigratoryRelationship(
			names[names.size() - 1][i],
			names[0][i],
			bidirectionalVertical,
			n
		);
}

#endif
