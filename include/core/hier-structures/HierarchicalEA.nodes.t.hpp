#ifndef CORE_HIER_STRUCTURES_HierarchicalEA_nodes_t
#define CORE_HIER_STRUCTURES_HierarchicalEA_nodes_t

#include "../HierarchicalEA.hpp"
#include "../PopulationNodeFactory.hpp"
#include "../../exception/MismatchedCountsException.hpp"

template <typename NodeType, typename... params>
void HierarchicalEA::addNode(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* populationToString,
	std::vector<EndCondition*> conditions,
	std::string nodeName,
	bool print,
	bool end,
	params... as
) {
	this->addNode(
		PopulationNodeFactory::createNode<NodeType>(
			populationSize,
			loci,
			objectives,
			populationToString,
			conditions,
			nodeName,
			as...
		),
		print,
		end
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addNodes(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* populationToString,
	std::vector<EndCondition*> conditions,
	std::vector<std::string> nodeNames,
	bool print,
	bool end,
	params... as
) {
	this->addNodes(
		PopulationNodeFactory::createNodes<NodeType>(
			populationSize,
			loci,
			objectives,
			populationToString,
			conditions,
			nodeNames,
			as...
		),
		print,
		end
	);
}

template <typename NodeType, typename... params>
void HierarchicalEA::addNodes(
	std::vector<unsigned int> populationSizes,
	std::vector<std::vector<Locus*>> loci,
	std::vector<std::vector<ObjectiveFunction*>> objectives,
	std::vector<ToStringFunction*> populationToStrings,
	std::vector<std::vector<EndCondition*>> conditions,
	std::vector<std::string> nodeNames,
	std::vector<bool> print,
	std::vector<bool> end,
	params... as
) {
	if (!this->compareVectorLengths(
		populationSizes,
		loci,
		objectives,
		populationToStrings,
		conditions,
		nodeNames,
		print,
		end
	)) throw MismatchedCountsException();

	for (unsigned int i = 0; i < nodeNames.size(); i++)
		this->addNode(
			PopulationNodeFactory::createNode(
				populationSizes[i],
				loci[i],
				objectives[i],
				populationToStrings[i],
				conditions[i],
				nodeNames[i],
				as...
			),
			print[i],
			end[i]
		);
}

#endif
