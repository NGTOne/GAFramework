#include "PopulationNode.hpp"
#include "PopulationFormula.hpp"
#include "migration/MigratoryRelationship.hpp"
#include "migration/TranslationFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "AggregationFunction.hpp"
#include "ObjectiveFunction.hpp"
#include "ToStringFunction.hpp"
#include "hier-structures/TreeBuilder.hpp"
#include <vector>
#include <tuple>
#include <string>
#pragma once

using namespace std;

class HierarchicalEA {
	private:

	protected:
	vector<PopulationNode *> nodes;
	vector<string> nodesToPrint;
	vector<string> evolutionOrder;
	vector<string> endDictators;
	vector<MigratoryRelationship> migrations;
	unsigned int maxEpochs;

	vector<PopulationNode *> evolutionNodes;
	vector<PopulationNode *> printNodes;
	vector<PopulationNode *> endConditionDictatorNodes;

	void buildNodeSet(
		vector<string> targetNames,
		vector <PopulationNode *> & targetSet
	);
	void buildEvolutionNodes();
	void buildPrintNodes();
	void buildEndDictators();
	void migrate();

	void checkNodesExist(vector<string> names);
	bool done(unsigned int currentEpoch);

	template <typename vec, typename vec2, typename... params>
	bool compareVectorLengths(
		vec initial,
		vec2 compare,
		params... vectors
	);

	template <typename vec, typename vec2>
	bool compareVectorLengths(vec initial, vec2 compare);

	template<typename vec>
	std::vector<vec> wrapForPass(
		vec original,
		std::vector<unsigned int> counts
	);

	public:
	HierarchicalEA();
	HierarchicalEA(unsigned int maxEpochs);
	~HierarchicalEA();

	// Kept separate from the destructor because we might want to keep them
	void deleteAllNodes();

	void run(bool verbose);

	void addNode(PopulationNode * node, bool print);
	void addNode(PopulationNode * node, bool print, bool end);
	void addNodes(
		std::vector<PopulationNode*> nodes,
		bool print,
		bool end
	);
	void addNodes(
		vector<PopulationNode*> nodes,
		vector<bool> print,
		vector<bool> end
	);
	void removeNode(string name);

	void setNodesToPrint(vector<string> names);
	void setEvolutionOrder(vector<string> names);
	void setEndConditionDictatorNodes(vector<string> names);
	PopulationNode * getNodeByName(string name);

	template<typename MetaNodeType, typename... params>
	void addMetaPopulation(
		bool clobberExistingObjectives,
		unsigned int populationSize,
		std::tuple<
			std::vector<std::string>,
			ApportionmentFunction *,
			AggregationFunction *
		> nodes,
		std::vector<ObjectiveFunction*> flattenedObjectives,
		ToStringFunction * flattenedToString,
		std::vector<EndCondition*> conditions,
		std::string metaNodeName,
		params... as
	);

	template<typename MetaNodeType, typename... params>
	void addMetaPopulation(
		bool clobberExistingObjectives,
		unsigned int populationSize,
		std::vector<std::tuple<
			std::string,
			ApportionmentFunction *,
			AggregationFunction *
		>> nodes,
		std::vector<ObjectiveFunction*> flattenedObjectives,
		ToStringFunction * flattenedToString,
		std::vector<EndCondition*> conditions,
		std::string metaNodeName,
		params... as
	);

	template<typename NodeType, typename... params>
	void addMigratoryRing(
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
	);

	template<typename NodeType, typename... params>
	void addMigratoryTorus(
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
	);

	void addMigratoryRelationship(
		string from,
		string to,
		bool bidirectional,
		unsigned int n
	);

	void addMigratoryRelationship(
		string from,
		string to,
		unsigned int n,
		TranslationFunction toTranslate
	);

	void addMigratoryRelationship(
		string from,
		string to,
		unsigned int n,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula * formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		TreeBuilder treeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula * formula,
		std::vector<std::vector<Locus*>> contextLoci,
		ObjectiveFunction * globalObjective,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		TreeBuilder treeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula * formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<std::vector<ObjectiveFunction*>> objectives,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		TreeBuilder treeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula * formula,
		std::vector<std::vector<std::vector<Locus*>>> contextLoci,
		std::vector<std::vector<std::vector<ObjectiveFunction*>>>
			objectives,
		std::vector<std::vector<ToStringFunction*>> toStrings,
		std::vector<std::vector<std::vector<EndCondition*>>>
			conditions,
		TreeBuilder treeSpec,
		std::vector<std::vector<bool>> print,
		std::vector<std::vector<bool>> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula * formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		std::vector<std::vector<std::string>> names,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula * formula,
		std::vector<std::vector<Locus*>> contextLoci,
		ObjectiveFunction * globalObjective,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		std::vector<std::vector<std::string>> names,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula * formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<std::vector<ObjectiveFunction*>> objectives,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		std::vector<std::vector<std::string>> names,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula * formula,
		std::vector<std::vector<std::vector<Locus*>>> contextLoci,
		std::vector<std::vector<std::vector<ObjectiveFunction*>>>
			objectives,
		std::vector<std::vector<ToStringFunction*>> toStrings,
		std::vector<std::vector<std::vector<EndCondition*>>>
			conditions,
		std::vector<std::vector<std::string>> names,
		std::vector<std::vector<bool>> print,
		std::vector<std::vector<bool>> end,
		params... as
	);
};

template <typename vec, typename vec2, typename... params>
bool HierarchicalEA::compareVectorLengths(
	vec initial,
	vec2 compare,
	params... vectors
) {
	if (initial.size() != compare.size()) return false;
	return this->compareVectorLengths(initial, vectors...);
}

template <typename vec, typename vec2>
bool HierarchicalEA::compareVectorLengths(vec initial, vec2 compare) {
	return initial.size() == compare.size();
}

template <typename vec>
std::vector<vec> HierarchicalEA::wrapForPass(
	vec original,
	std::vector<unsigned int> counts
) {
	std::vector<vec> wrapped;
	for (unsigned int i = 0; i < original.size(); i++)
		wrapped.push_back(vec(counts[i], original[i]));

	return wrapped;
}
