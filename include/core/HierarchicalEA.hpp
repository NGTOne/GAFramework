#include "PopulationNode.hpp"
#include "PopulationFormula.hpp"
#include "migration/MigratoryRelationship.hpp"
#include "migration/TranslationFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "AggregationFunction.hpp"
#include "ObjectiveFunction.hpp"
#include "ToStringFunction.hpp"
#include "builders/TreeBuilder.hpp"
#include "builders/LatticeBuilder.hpp"
#include "instruments/HierInstrument.hpp"
#include <vector>
#include <tuple>
#include <string>
#pragma once

#define OVERALL_COEV_NAME "Overall Coevolution"

class HierarchicalEA {
	private:

	protected:
	std::vector<PopulationNode*> nodes;
	std::vector<std::string> nodesToPrint;
	std::vector<std::string> evolutionOrder;
	std::vector<std::string> endDictators;
	std::vector<MigratoryRelationship> migrations;
	unsigned int maxEpochs;

	std::vector<PopulationNode*> evolutionNodes;
	std::vector<PopulationNode*> printNodes;
	std::vector<PopulationNode*> endConditionDictatorNodes;

	void buildNodeSet(
		std::vector<std::string> targetNames,
		std::vector<PopulationNode*>& targetSet
	);
	void buildEvolutionNodes();
	void buildPrintNodes();
	void buildEndDictators();
	void migrate();

	void checkNodesExist(std::vector<std::string> names);
	bool done(unsigned int currentEpoch);
	bool isNodePrinted(std::string node);
	bool isNodeEndDictator(std::string node);

	unsigned int findHighestCoevIndex();
	std::string getNextCoevName();
	PopulationNode* findCoevRootNode(std::vector<std::string> coevNodes);

	template <typename vec, typename vec2, typename... params>
	bool compareVectorLengths(
		vec initial,
		vec2 compare,
		params... vectors
	);

	template <typename vec, typename vec2>
	bool compareVectorLengths(vec initial, vec2 compare);

	template <typename T>
	std::vector<T> wrapForPass(T original, unsigned int count);

	template<typename vec>
	std::vector<vec> wrapForPass(
		vec original,
		std::vector<unsigned int> counts,
		unsigned int offset = 0
	);

	std::vector<ObjectiveFunction*> makeApportionments(
		PopulationNode* upperNode,
		std::vector<ApportionmentFunction*> functions,
		std::vector<AggregationFunction*> aggregators,
		std::vector<unsigned int> tryOns
	);

	void addApportionments(
		std::vector<PopulationNode*> upperNodes,
		std::vector<PopulationNode*> lowerNodes,
		std::vector<std::vector<ApportionmentFunction*>>
			apportionments,
		std::vector<std::vector<AggregationFunction*>> aggregators,
		std::vector<std::vector<unsigned int>> tryOns
	);

	void addApportionments(
		std::vector<PopulationNode*> upperNodes,
		std::vector<PopulationNode*> lowerNodes,
		std::vector<unsigned int> counts,
		std::vector<std::vector<ApportionmentFunction*>>
			apportionments,
		std::vector<std::vector<AggregationFunction*>> aggregators,
		std::vector<std::vector<unsigned int>> tryOns
	);

	template <typename T>
	std::vector<std::vector<std::vector<T>>> getNestedEmptyVector(
		std::vector<unsigned int> counts,
		unsigned int offset = 0
	);

	public:
	HierarchicalEA(unsigned int maxEpochs);
	HierarchicalEA(unsigned int maxEpochs, unsigned int globalSeed);
	~HierarchicalEA();

	// Kept separate from the destructor because we might want to keep them
	void deleteAllNodes();

	void run(bool verbose);

	void addNode(PopulationNode* node, bool print);
	void addNode(PopulationNode* node, bool print, bool end);
	void addNodes(
		std::vector<PopulationNode*> nodes,
		bool print,
		bool end
	);
	void addNodes(
		std::vector<PopulationNode*> nodes,
		std::vector<bool> print,
		std::vector<bool> end
	);
	void duplicateNode(
		std::string original,
		std::vector<std::string> newNames
	);
	void removeNode(std::string name);

	void setNodesToPrint(std::vector<std::string> names);
	void setEvolutionOrder(std::vector<std::string> names);
	void setEndConditionDictatorNodes(std::vector<std::string> names);
	PopulationNode* getNodeByName(std::string name);

	template <typename NodeType, typename... params>
	void addNode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition*> conditions,
		std::string nodeName,
		bool print,
		bool end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addNodes(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition*> conditions,
		std::vector<std::string> nodeNames,
		bool print,
		bool end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addNodes(
		std::vector<unsigned int> populationSizes,
		std::vector<std::vector<Locus*>> loci,
		std::vector<std::vector<ObjectiveFunction*>> objectives,
		std::vector<ToStringFunction*> populationToString,
		std::vector<std::vector<EndCondition*>> conditions,
		std::vector<std::string> nodeNames,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template<typename MetaNodeType, typename... params>
	void addMetaPopulation(
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
	);

	template<typename MetaNodeType, typename... params>
	void addMetaPopulation(
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
	);

	template<typename NodeType, typename... params>
	void addMigratoryRing(
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
	);

	template<typename NodeType, typename... params>
	void addMigratoryTorus(
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
	);

	void addMigratoryRelationship(
		std::string from,
		std::string to,
		bool bidirectional,
		unsigned int n
	);

	void addMigratoryRelationship(
		std::string from,
		std::string to,
		unsigned int n,
		TranslationFunction toTranslate
	);

	void addMigratoryRelationship(
		std::string from,
		std::string to,
		unsigned int n,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);

	void addMigratoryRing(
		std::vector<std::string> nodes,
		bool bidirectional,
		unsigned int n
	);

	void addMigratoryRing(
		std::string originalNode,
		std::vector<std::string> newNodeNames,
		bool bidirectional,
		unsigned int n
	);

	template <typename NodeType, typename... params>
	void addCooperativeCoevolution(
		std::vector<ObjectiveFunction*> overallObjectives,
		std::vector<EndCondition*> overallConditions,
		ToStringFunction* overallToString,
		unsigned int numThreads,
		unsigned int populationSize,
		std::vector<Locus*> loci,
		ApportionmentFunction* apportionment,
		AggregationFunction* aggregator,
		ToStringFunction* toString,
		std::vector<EndCondition*> conditions,
		std::vector<std::string> nodeNames,
		bool print,
		bool end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addCooperativeCoevolution(
		std::vector<ObjectiveFunction*> overallObjectives,
		std::vector<EndCondition*> overallConditions,
		ToStringFunction* overallToString,
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
	);

	template <typename MetaNodeType, typename... params>
	void addCooperativeCoevMetaNode(
		std::vector<std::string> coopNodes,
		unsigned int numThreads,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction* toString,
		std::vector<EndCondition*> conditions,
		std::string metaNodeName,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula* formula,
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
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		ObjectiveFunction* globalObjective,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		TreeBuilder treeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula* formula,
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
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<ObjectiveFunction*> topObjectives,
		std::vector<std::vector<ApportionmentFunction*>>
			apportionments,
		std::vector<std::vector<AggregationFunction*>> aggregators,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		TreeBuilder treeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<ObjectiveFunction*> topObjectives,
		std::vector<std::vector<ApportionmentFunction*>>
			apportionments,
		std::vector<std::vector<AggregationFunction*>> aggregators,
		std::vector<std::vector<unsigned int>> tryOns,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		TreeBuilder treeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula* formula,
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
	void addConstructiveTree(
		PopulationFormula* formula,
		std::vector<std::vector<std::vector<Locus*>>> contextLoci,
		std::vector<ObjectiveFunction*> topObjectives,
		std::vector<std::vector<std::vector<ApportionmentFunction*>>>
			apportionments,
		std::vector<std::vector<std::vector<AggregationFunction*>>>
			aggregators,
		std::vector<std::vector<std::vector<unsigned int>>> tryOns,
		std::vector<std::vector<ToStringFunction*>> toStrings,
		std::vector<std::vector<std::vector<EndCondition*>>>
			conditions,
		TreeBuilder treeSpec,
		std::vector<std::vector<bool>> print,
		std::vector<std::vector<bool>> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveTree(
		PopulationFormula* formula,
		std::vector<std::vector<std::vector<Locus*>>> contextLoci,
		std::vector<std::vector<std::vector<ObjectiveFunction*>>>
			objectives,
		std::vector<std::vector<std::vector<ApportionmentFunction*>>>
			apportionments,
		std::vector<std::vector<std::vector<AggregationFunction*>>>
			aggregators,
		std::vector<std::vector<std::vector<unsigned int>>> tryOns,
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
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		LatticeBuilder latticeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		ObjectiveFunction* globalObjective,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		LatticeBuilder latticeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<std::vector<ObjectiveFunction*>> objectives,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		LatticeBuilder latticeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<ObjectiveFunction*> topObjectives,
		std::vector<std::vector<ApportionmentFunction*>>
			apportionments,
		std::vector<std::vector<AggregationFunction*>> aggregators,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		LatticeBuilder latticeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula* formula,
		std::vector<std::vector<Locus*>> contextLoci,
		std::vector<ObjectiveFunction *> topObjectives,
		std::vector<std::vector<ApportionmentFunction*>>
			apportionments,
		std::vector<std::vector<AggregationFunction*>> aggregators,
		std::vector<std::vector<unsigned int>> tryOns,
		std::vector<ToStringFunction*> toStrings,
		std::vector<std::vector<EndCondition*>> conditions,
		LatticeBuilder latticeSpec,
		std::vector<bool> print,
		std::vector<bool> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula* formula,
		std::vector<std::vector<std::vector<Locus*>>> contextLoci,
		std::vector<std::vector<std::vector<ObjectiveFunction*>>>
			objectives,
		std::vector<std::vector<ToStringFunction*>> toStrings,
		std::vector<std::vector<std::vector<EndCondition*>>>
			conditions,
		LatticeBuilder latticeSpec,
		std::vector<std::vector<bool>> print,
		std::vector<std::vector<bool>> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula* formula,
		std::vector<std::vector<std::vector<Locus*>>> contextLoci,
		std::vector<ObjectiveFunction *> topObjectives,
		std::vector<std::vector<std::vector<ApportionmentFunction*>>>
			apportionments,
		std::vector<std::vector<std::vector<AggregationFunction*>>>
			aggregators,
		std::vector<std::vector<std::vector<unsigned int>>> tryOns,
		std::vector<std::vector<ToStringFunction*>> toStrings,
		std::vector<std::vector<std::vector<EndCondition*>>>
			conditions,
		LatticeBuilder latticeSpec,
		std::vector<std::vector<bool>> print,
		std::vector<std::vector<bool>> end,
		params... as
	);

	template <typename NodeType, typename... params>
	void addConstructiveLattice(
		PopulationFormula* formula,
		std::vector<std::vector<std::vector<Locus*>>> contextLoci,
		std::vector<std::vector<std::vector<ObjectiveFunction*>>>
			objectives,
		std::vector<std::vector<std::vector<ApportionmentFunction*>>>
			apportionments,
		std::vector<std::vector<std::vector<AggregationFunction*>>>
			aggregators,
		std::vector<std::vector<std::vector<unsigned int>>> tryOns,
		std::vector<std::vector<ToStringFunction*>> toStrings,
		std::vector<std::vector<std::vector<EndCondition*>>>
			conditions,
		LatticeBuilder latticeSpec,
		std::vector<std::vector<bool>> print,
		std::vector<std::vector<bool>> end,
		params... as
	);

	template <typename InstrType>
	void addInstrumentation(
		std::string outFile,
		bool runImmediately = false
	);

	template <typename InstrType>
	void addInstrumentation(
		std::string node,
		std::string outFile,
		bool runImmediately = false
	);

	template <typename InstrType>
	void addInstrumentation(
		std::vector<std::string> nodes,
		std::string outFile,
		bool runImmediately = false
	);

	template <typename InstrType>
	void addInstrumentation(
		std::vector<std::string> nodes,
		std::vector<std::string> outFiles,
		bool runImmediately = false
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

template <typename T>
std::vector<T> HierarchicalEA::wrapForPass(T original, unsigned int count) {
	return std::vector<T>(count, original);
}

template <typename vec>
std::vector<vec> HierarchicalEA::wrapForPass(
	vec original,
	std::vector<unsigned int> counts,
	unsigned int offset
) {
	std::vector<vec> wrapped;
	for (unsigned int i = offset; i < counts.size(); i++)
		wrapped.push_back(vec(counts[i], original[i-offset]));

	return wrapped;
}

template <typename T>
std::vector<std::vector<std::vector<T>>> HierarchicalEA::getNestedEmptyVector(
	std::vector<unsigned int> counts,
	unsigned int offset
) {
	std::vector<std::vector<std::vector<T>>> empty;
	for (unsigned int i = offset; i < counts.size(); i++)
		empty.push_back(std::vector<std::vector<T>>(
			counts[i],
			std::vector<T>()
		));

	return empty;
}
