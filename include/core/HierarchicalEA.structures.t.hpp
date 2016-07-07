#include "HierarchicalEA.hpp"
#include "PopulationNodeFactory.hpp"
#include "../exception/MismatchedCountsException.hpp"

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

template<typename NodeType, typename... params>
void HierarchicalEA::addMigratoryTorus(
	bool bidirectionalHorizontal,
	bool bidirectionalVertical,
	unsigned int n,
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction * nodeToString,
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
	if (
		names.size() != contextLoci.size()
		|| (!objectives.empty() && names.size() != objectives.size())
		|| names.size() != toStrings.size()
		|| names.size() != conditions.size()
		|| names.size() != print.size()
		|| names.size() != end.size()
	) throw MismatchedCountsException(); // TODO: Refactor this

	std::vector<Locus*> levelLoci;
	std::vector<PopulationNode*> levelNodes;
	for (unsigned int i = names.size() - 1; i >= 0; i--) {
		levelLoci.insert(
			levelLoci.end(),
			contextLoci[i].begin(),
			contextLoci[i].end()
		);

		levelNodes = PopulationNodeFactory::createNodes<NodeType>(
			formula->getPopulationSize(levelLoci.size()),
			levelLoci,
			(!objectives.empty() ? objectives[i]
				: std::vector<ObjectiveFunction*>({})),
			toStrings[i],
			conditions[i],
			names[i],
			as...
		);

		this->addNodes(levelNodes, print[i], end[i]);
		levelLoci.clear();
		for (unsigned int k = 0; k < levelNodes.size(); k++)
			levelLoci.push_back(
				new PopulationLocus(levelNodes[k])
			);
	}

	// Clean up - otherwise the "head" nodes will have unused loci
	// pointing to them
	for (unsigned int i = 0; i < levelLoci.size(); i++)
		delete(levelLoci[i]);
}
