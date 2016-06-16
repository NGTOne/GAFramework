#include "PopulationNode.hpp"
#include "migration/MigratoryRelationship.hpp"
#include "migration/TranslationFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "AggregationFunction.hpp"
#include "ObjectiveFunction.hpp"
#include "ToStringFunction.hpp"
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
	int maxEpochs;

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
	bool done(int currentEpoch);

	public:
	HierarchicalEA();
	HierarchicalEA(int maxEpochs);
	~HierarchicalEA();

	// Kept separate from the destructor because we might want to keep them
	void deleteAllNodes();

	void run(bool verbose);

	void addNode(PopulationNode * node, bool print);
	void addNode(PopulationNode * node, bool print, bool end);
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

	void addMetaPopulation(
		PopulationNode * metaNode,
		vector<ObjectiveFunction*> flattenedObjectives,
		ToStringFunction * flattenedToString,
		string topNode,
		tuple<
			ApportionmentFunction *,
			AggregationFunction *
		> topNodeApportionment,
		vector<tuple<
			string,
			ApportionmentFunction *,
			AggregationFunction *
		>> secondaryNodes
	);

	void addMigratoryRelationship(
		string from,
		string to,
		bool bidirectional,
		int n
	);

	void addMigratoryRelationship(
		string from,
		string to,
		int n,
		TranslationFunction toTranslate
	);

	void addMigratoryRelationship(
		string from,
		string to,
		int n,
		TranslationFunction toTranslate,
		TranslationFunction fromTranslate
	);
};
