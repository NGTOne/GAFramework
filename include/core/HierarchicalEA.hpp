#include "PopulationNode.hpp"
#include "migration/MigratoryRelationship.hpp"
#include "migration/TranslationFunction.hpp"
#include <vector>
#include <string>
#pragma once

using namespace std;

class HierarchicalEA {
	private:

	protected:
	vector<PopulationNode *> nodes;
	vector<string> nodeNames;
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
		vector <PopulationNode *> * targetSet
	);
	void buildEvolutionNodes();
	void buildPrintNodes();
	void buildEndDictators();
	void migrate();

	void checkNodesExist(vector<string> names);
	bool done(int currentEpoch);

	PopulationNode * getNodeByName(string name);

	public:
	HierarchicalEA(int maxEpochs);
	~HierarchicalEA();

	void run(bool verbose);

	void addNode(PopulationNode * node, string name, bool print);
	void addNode(PopulationNode * node, string name, bool print, bool end);
	void removeNode(string name);

	void setNodesToPrint(vector<string> names);
	void setEvolutionOrder(vector<string> names);
	void setEndConditionDictatorNodes(vector<string> names);

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
