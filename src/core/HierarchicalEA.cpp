#include "core/HierarchicalEA.hpp"
#include "exception/NodeAlreadyExistsException.hpp"
#include "exception/InvalidNodeException.hpp"
#include "exception/NoNodesException.hpp"
#include "exception/NoEvolutionOrderException.hpp"

#include <iostream>
#include <algorithm>

HierarchicalEA::HierarchicalEA(int maxEpochs) {
	this->maxEpochs = maxEpochs;
}

HierarchicalEA::~HierarchicalEA() {}

void HierarchicalEA::addNode(PopulationNode * node, string name, bool print) {
	for (int i = 0; i < nodeNames.size(); i++) {
		if (nodeNames[i] == name or nodes[i] == node) {
			throw NodeAlreadyExistsException();
		}
	}
	nodes.push_back(node);
	nodeNames.push_back(name);
	if (print) nodesToPrint.push_back(name);
}

void HierarchicalEA::removeNode(string name) {
	for (int i = 0; i < nodeNames.size(); i++) {
		string nodeName = nodeNames[i];
		if (nodeName == name) {
			nodeNames.erase(nodeNames.begin()+i);
			nodes.erase(nodes.begin()+i);
			break;
		}
	}

	for (int i = 0; i < nodesToPrint.size(); i++) {
		if ((nodesToPrint[i]) == name) {
			nodesToPrint.erase(nodesToPrint.begin()+i);
		}
	}
}

void HierarchicalEA::checkNodesExist(vector<string> names) {
	for (int i = 0; i < names.size(); i++) {
		bool exists = false;

		for (int k = 0; k < nodeNames.size(); k++) {
			if (nodeNames[k] == names[i]) exists = true;
		}

		if (!exists) throw InvalidNodeException();
	}
}

void HierarchicalEA::setNodesToPrint(vector<string> names) {
	checkNodesExist(names);
	nodesToPrint.clear();
	nodesToPrint = names;
}

void HierarchicalEA::setEvolutionOrder(vector<string> names) {
	checkNodesExist(names);
	evolutionOrder.clear();
	evolutionOrder = names;
}

void HierarchicalEA::buildNodeSet(
	vector<string> targetNames,
	vector<PopulationNode *> targetSet
) {
	if (nodes.empty()) throw NoNodesException();
	checkNodesExist(targetNames);

	for (int i = 0; i < targetNames.size(); i++) {
		string name = targetNames[i];
		for (int k = 0; k < nodeNames.size(); k++) {
			string realName = nodeNames[k];
			if (name == realName) {
				targetSet.push_back(nodes[k]);
				break;
			}
		}
	}
}

void HierarchicalEA::buildEvolutionNodes() {
	if (evolutionOrder.empty()) throw NoEvolutionOrderException();
	evolutionNodes.clear();
	buildNodeSet(evolutionOrder, evolutionNodes);
}

void HierarchicalEA::buildPrintNodes() {
	if (nodes.empty()) throw NoNodesException();
	printNodes.clear();
	buildNodeSet(nodesToPrint, printNodes);
}

void HierarchicalEA::run(bool verbose) {
	buildEvolutionNodes();
	buildPrintNodes();
	cout << "Before:\n";
	for (int k = 0; k < printNodes.size(); k++) {
		cout << printNodes[k]->toString();
	}

	for (int i = 0; i < maxEpochs; i++) {
		for (int k = 0; k < evolutionNodes.size(); k++) {
			evolutionNodes[k]->runGenerations();
		}

		cout << "After epoch " << i << ":\n";
		for (int k = 0; k < printNodes.size(); k++) {
			cout << printNodes[k]->toString();
		}
	}
}
