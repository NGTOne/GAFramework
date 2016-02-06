#include "PopulationNode.hpp"
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
	vector<MigratoryRelationship *> migrations;

	int maxEpochs;

	public:
	HierachicalEA();
	~HierarchicalEA();

	void run(bool verbose);

	void addNode(PopulationNode * node, string name, bool print);
	void removeNode(string name);
	void setNodesToPrint(vector<string> names);

	void setEvolutionOrder(vector<string> names);

	void addMigratoryRelationship(
		string from,
		string to,
		bool bidirectional
	);
};
