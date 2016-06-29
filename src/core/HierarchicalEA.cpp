#include "core/HierarchicalEA.hpp"
#include "exception/NodeAlreadyExistsException.hpp"
#include "exception/InvalidNodeException.hpp"
#include "exception/NoNodesException.hpp"
#include "exception/NoEvolutionOrderException.hpp"
#include "exception/MismatchedCountsException.hpp"
#include "core/gc/NodeGarbageCollector.hpp"
#include "core/meta/MetaPopulationFactory.hpp"

#include <iostream>
#include <algorithm>

HierarchicalEA::HierarchicalEA() {}

HierarchicalEA::HierarchicalEA(int maxEpochs) {
	this->maxEpochs = maxEpochs;
}

HierarchicalEA::~HierarchicalEA() {}

void HierarchicalEA::deleteAllNodes() {
	NodeGarbageCollector gc;
	gc.deleteNodes(this->nodes);

	this->nodesToPrint.clear();
	this->evolutionOrder.clear();
	this->endDictators.clear();
	this->evolutionNodes.clear();
	this->printNodes.clear();
	this->endConditionDictatorNodes.clear();
}

void HierarchicalEA::addNode(PopulationNode * node, bool print) {
	this->addNode(node, print, false);
}

void HierarchicalEA::addNode(
	PopulationNode* node,
	bool print,
	bool end
) {
	for (unsigned int i = 0; i < this->nodes.size(); i++)
		if (this->nodes[i] == node) throw NodeAlreadyExistsException();

	this->nodes.push_back(node);
	if (print) this->nodesToPrint.push_back(node->name());
	if (end) this->endDictators.push_back(node->name());
}

void HierarchicalEA::addNodes(
	vector<PopulationNode*> nodes,
	vector<bool> print,
	vector<bool> end
) {
	if (nodes.size() != print.size() || nodes.size() != end.size())
		throw MismatchedCountsException();

	for (unsigned int i = 0; i < nodes.size(); i++)
		this->addNode(nodes[i], print[i], end[i]);
}

// TODO: Refactor this a bit
void HierarchicalEA::removeNode(string name) {
	PopulationNode * node = this->getNodeByName(name);
	for (unsigned int i = 0; i < this->nodes.size(); i++)
		if (node == this->nodes[i]) {
			this->nodes.erase(this->nodes.begin()+i);
			break;
		}

	for (unsigned int i = 0; i < this->nodesToPrint.size(); i++)
		if (this->nodesToPrint[i] == name)
			this->nodesToPrint.erase(this->nodesToPrint.begin()+i);

	for (unsigned int i = 0; i < this->endDictators.size(); i++)
		if (this->endDictators[i] == name)
			this->endDictators.erase(this->endDictators.begin()+i);
}

void HierarchicalEA::checkNodesExist(vector<string> names) {
	for (unsigned int i = 0; i < names.size(); i++)
		if (this->getNodeByName(names[i]) == NULL)
			throw InvalidNodeException();
}

void HierarchicalEA::setNodesToPrint(vector<string> names) {
	this->checkNodesExist(names);
	this->nodesToPrint.clear();
	this->nodesToPrint = names;
}

void HierarchicalEA::setEvolutionOrder(vector<string> names) {
	this->checkNodesExist(names);
	this->evolutionOrder.clear();
	this->evolutionOrder = names;
}

void HierarchicalEA::setEndConditionDictatorNodes(vector<string> names) {
	this->checkNodesExist(names);
	this->endDictators.clear();
	this->endDictators = names;
}

PopulationNode * HierarchicalEA::getNodeByName(string name) {
	for (unsigned int i = 0; i < this->nodes.size(); i++)
		if (this->nodes[i]->name() == name) return this->nodes[i];

	return NULL;
}

void HierarchicalEA::buildNodeSet(
	vector<string> targetNames,
	vector<PopulationNode *> & targetSet
) {
	if (this->nodes.empty()) throw NoNodesException();
	this->checkNodesExist(targetNames);

	for (unsigned int i = 0; i < targetNames.size(); i++)
		targetSet.push_back(this->getNodeByName(targetNames[i]));
}

void HierarchicalEA::buildEvolutionNodes() {
	if (evolutionOrder.empty()) throw NoEvolutionOrderException();
	this->evolutionNodes.clear();
	this->buildNodeSet(this->evolutionOrder, this->evolutionNodes);
}

void HierarchicalEA::buildPrintNodes() {
	this->printNodes.clear();
	this->buildNodeSet(this->nodesToPrint, this->printNodes);
}

void HierarchicalEA::buildEndDictators() {
	this->endConditionDictatorNodes.clear();
	this->buildNodeSet(this->endDictators, this->endConditionDictatorNodes);
}

void HierarchicalEA::migrate() {
	for (unsigned int i = 0; i < this->migrations.size(); i++)
		this->migrations[i].migrate();
}

bool HierarchicalEA::done(int currentEpoch) {
	bool done = true;
	if (currentEpoch >= this->maxEpochs - 1) {
		cout << "Hierarchical EA ended because maximum epoch count"
			<< " was reached.\n";
		return done;
	}

	if (this->endConditionDictatorNodes.size() == 0) return false;

	for (unsigned int i = 0; i < this->endConditionDictatorNodes.size(); i++) {
		if (!this->endConditionDictatorNodes[i]->done()) {
			done = false;
			break;
		}
	}

	if (done) cout << "Hierarchical EA ended because all specified"
		<< " population nodes reported reaching their ending conditions.\n";

	return done;
}

// TODO: Make verbosity option actually mean something
void HierarchicalEA::run(bool verbose) {
	this->buildEvolutionNodes();
	this->buildPrintNodes();
	this->buildEndDictators();
	cout << "Before:\n";
	cout << string(80, '=') << "\n";
	for (unsigned int i = 0; i < this->printNodes.size(); i++) {
		cout << "Node " << this->nodesToPrint[i] << ":\n";
		cout << this->printNodes[i]->toString();
		cout << string(80, '-') << "\n";
	}

	for (int i = 0; i < this->maxEpochs; i++) {
		for (unsigned int k = 0; k < this->evolutionNodes.size(); k++)
			this->evolutionNodes[k]->nextIteration();

		// TODO: Optimize fitness evaluation overall
		// There's too many evaluations required right now in order to
		// do everything
		for (unsigned int k = 0; k < this->evolutionNodes.size(); k++)
			this->evolutionNodes[k]->evaluateFitnesses();

		this->migrate();

		// Because humans count from 1, we add 1 to our epoch counter
		cout << "After epoch " << i+1 << ":\n";
		cout << string(80, '=') << "\n";
		for (unsigned int k = 0; k < this->printNodes.size(); k++) {
			cout << "Node " << this->nodesToPrint[k] << ":\n";
			cout << this->printNodes[k]->toString();
			cout << string(80, '-') << "\n";
		}

		if (this->done(i)) break;
	}
}

void HierarchicalEA::addMetaPopulation(
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
) {
	vector<tuple<
		PopulationNode *,
		ApportionmentFunction *,
		AggregationFunction *
	>> trueSecondaryNodes;

	for (unsigned int i = 0; i < secondaryNodes.size(); i++)
		trueSecondaryNodes.push_back(make_tuple(
			this->getNodeByName(get<0>(secondaryNodes[i])),
			get<1>(secondaryNodes[i]),
			get<2>(secondaryNodes[i])
		));

	this->addNode(
		MetaPopulationFactory::createMeta(
			metaNode,
			flattenedObjectives,
			flattenedToString,
			this->getNodeByName(topNode),
			topNodeApportionment,
			trueSecondaryNodes
		),
		false,
		false
	);
}

void HierarchicalEA::addMigratoryRelationship(
	string from,
	string to,
	bool bidirectional,
	int n
) {
	if (bidirectional) {
		this->addMigratoryRelationship(
			from,
			to,
			n,
			TranslationFunction(),
			TranslationFunction()
		);
	} else {
		this->addMigratoryRelationship(
			from,
			to,
			n,
			TranslationFunction()
		);
	}
}

void HierarchicalEA::addMigratoryRelationship(
	string from,
	string to,
	int n,
	TranslationFunction toTranslate
) {
	PopulationNode * fromNode, * toNode;
	fromNode = this->getNodeByName(from);
	toNode = this->getNodeByName(to);
	this->migrations.push_back(MigratoryRelationship(
		fromNode,
		toNode,
		n,
		toTranslate
	));
}

void HierarchicalEA::addMigratoryRelationship(
	string from,
	string to,
	int n,
	TranslationFunction toTranslate,
	TranslationFunction fromTranslate
) {
	PopulationNode * fromNode, * toNode;
	fromNode = this->getNodeByName(from);
	toNode = this->getNodeByName(to);
	this->migrations.push_back(MigratoryRelationship(
		fromNode,
		toNode,
		n,
		toTranslate,
		fromTranslate
	));
}
