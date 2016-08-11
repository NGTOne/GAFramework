#include "core/HierarchicalEA.hpp"
#include "exception/NodeAlreadyExistsException.hpp"
#include "exception/InvalidNodeException.hpp"
#include "exception/NoNodesException.hpp"
#include "exception/NoEvolutionOrderException.hpp"
#include "exception/MismatchedCountsException.hpp"
#include "exception/CoevConstructionException.hpp"
#include "core/Apportionment.hpp"
#include "loci/PopulationLocus.hpp"
#include "nodes/NonOptimizingNode.hpp"
#include "core/HierRNG.hpp"
#include "core/HierGC.hpp"

#include <iostream>
#include <algorithm>
#include <regex>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/predicate.hpp>

HierarchicalEA::HierarchicalEA(unsigned int maxEpochs) {
	this->maxEpochs = maxEpochs;
	HierRNG::initialize();
}

HierarchicalEA::HierarchicalEA(
	unsigned int maxEpochs,
	unsigned int globalSeed
) {
	this->maxEpochs = maxEpochs;
	HierRNG::initialize(globalSeed);
}

HierarchicalEA::~HierarchicalEA() {}

void HierarchicalEA::deleteAllNodes() {
	HierGC::cleanUp();

	this->nodesToPrint.clear();
	this->evolutionOrder.clear();
	this->endDictators.clear();
	this->evolutionNodes.clear();
	this->printNodes.clear();
	this->endConditionDictatorNodes.clear();
}

void HierarchicalEA::addNode(PopulationNode* node, bool print) {
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

	HierGC::registerObject(node);
}

void HierarchicalEA::addNodes(
	std::vector<PopulationNode*> nodes,
	bool print,
	bool end
) {
	for (unsigned int i = 0; i < nodes.size(); i++)
		this->addNode(nodes[i], print, end);
}

void HierarchicalEA::addNodes(
	std::vector<PopulationNode*> nodes,
	std::vector<bool> print,
	std::vector<bool> end
) {
	if (nodes.size() != print.size() || nodes.size() != end.size())
		throw MismatchedCountsException();

	for (unsigned int i = 0; i < nodes.size(); i++)
		this->addNode(nodes[i], print[i], end[i]);
}

void HierarchicalEA::duplicateNode(
	std::string original,
	std::vector<std::string> newNames
) {
	PopulationNode* originalNode = this->getNodeByName(original);
	bool print = this->isNodePrinted(original);
	bool end = this->isNodeEndDictator(original);

	for (unsigned int i = 0; i < newNames.size(); i++)
		this->addNode(
			originalNode->duplicate(newNames[i]),
			print,
			end
		);
}

// TODO: Refactor this a bit
void HierarchicalEA::removeNode(std::string name) {
	PopulationNode* node = this->getNodeByName(name);
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

void HierarchicalEA::checkNodesExist(std::vector<std::string> names) {
	for (unsigned int i = 0; i < names.size(); i++)
		if (this->getNodeByName(names[i]) == NULL)
			throw InvalidNodeException();
}

void HierarchicalEA::setNodesToPrint(std::vector<std::string> names) {
	this->checkNodesExist(names);
	this->nodesToPrint.clear();
	this->nodesToPrint = names;
}

void HierarchicalEA::setEvolutionOrder(std::vector<std::string> names) {
	this->checkNodesExist(names);
	this->evolutionOrder.clear();
	this->evolutionOrder = names;
}

void HierarchicalEA::setEndConditionDictatorNodes(
	std::vector<std::string> names
) {
	this->checkNodesExist(names);
	this->endDictators.clear();
	this->endDictators = names;
}

PopulationNode* HierarchicalEA::getNodeByName(std::string name) {
	for (unsigned int i = 0; i < this->nodes.size(); i++)
		if (this->nodes[i]->name() == name) return this->nodes[i];

	return NULL;
}

void HierarchicalEA::buildNodeSet(
	std::vector<std::string> targetNames,
	std::vector<PopulationNode*> & targetSet
) {
	if (this->nodes.empty()) throw NoNodesException();
	this->checkNodesExist(targetNames);

	for (unsigned int i = 0; i < targetNames.size(); i++)
		targetSet.push_back(this->getNodeByName(targetNames[i]));
}

void HierarchicalEA::buildEvolutionNodes() {
	if (this->evolutionOrder.empty()) throw NoEvolutionOrderException();
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

bool HierarchicalEA::done(unsigned int currentEpoch) {
	bool done = true;
	if (currentEpoch >= this->maxEpochs - 1) {
		std::cout << "Hierarchical EA ended because maximum epoch count"
			<< " was reached.\n";
		return done;
	}

	if (this->endConditionDictatorNodes.size() == 0) return false;

	for (
		unsigned int i = 0;
		i < this->endConditionDictatorNodes.size();
		i++
	) if (!this->endConditionDictatorNodes[i]->done()) {
		done = false;
		break;
	}

	if (done) std::cout << "Hierarchical EA ended because all specified"
		<< " population nodes reported reaching their"
		<< " ending conditions.\n";

	return done;
}

bool HierarchicalEA::isNodePrinted(std::string node) {
	return std::find(
		this->nodesToPrint.begin(),
		this->nodesToPrint.end(),
		node
	) != this->nodesToPrint.end();
}

bool HierarchicalEA::isNodeEndDictator(std::string node) {
	return std::find(
		this->endDictators.begin(),
		this->endDictators.end(),
		node
	) != this->endDictators.end();
}

// TODO: Make verbosity option actually mean something
void HierarchicalEA::run(bool verbose) {
	this->buildEvolutionNodes();
	this->buildPrintNodes();
	this->buildEndDictators();
	std::cout << "Before:\n";
	std::cout << std::string(80, '=') << "\n";
	for (unsigned int i = 0; i < this->printNodes.size(); i++) {
		std::cout << "Node " << this->nodesToPrint[i] << ":\n";
		std::cout << this->printNodes[i]->toString();
		std::cout << std::string(80, '-') << "\n";
	}

	for (unsigned int i = 0; i < this->maxEpochs; i++) {
		for (unsigned int k = 0; k < this->evolutionNodes.size(); k++)
			this->evolutionNodes[k]->nextIteration();

		// TODO: Optimize fitness evaluation overall
		// There's too many evaluations required right now in order to
		// do everything
		for (unsigned int k = 0; k < this->evolutionNodes.size(); k++)
			this->evolutionNodes[k]->evaluateFitnesses();

		this->migrate();

		// Because humans count from 1, we add 1 to our epoch counter
		std::cout << "After epoch " << i+1 << ":\n";
		std::cout << std::string(80, '=') << "\n";
		for (unsigned int k = 0; k < this->printNodes.size(); k++) {
			std::cout << "Node " << this->nodesToPrint[k] << ":\n";
			std::cout << this->printNodes[k]->toString();
			std::cout << std::string(80, '-') << "\n";
		}

		if (this->done(i)) break;
	}
}

void HierarchicalEA::addMigratoryRelationship(
	std::string from,
	std::string to,
	bool bidirectional,
	unsigned int n
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
	std::string from,
	std::string to,
	unsigned int n,
	TranslationFunction toTranslate
) {
	this->migrations.push_back(MigratoryRelationship(
		this->getNodeByName(from),
		this->getNodeByName(to),
		n,
		toTranslate
	));
}

void HierarchicalEA::addMigratoryRelationship(
	std::string from,
	std::string to,
	unsigned int n,
	TranslationFunction toTranslate,
	TranslationFunction fromTranslate
) {
	this->migrations.push_back(MigratoryRelationship(
		this->getNodeByName(from),
		this->getNodeByName(to),
		n,
		toTranslate,
		fromTranslate
	));
}

void HierarchicalEA::addMigratoryRing(
	std::vector<std::string> nodes,
	bool bidirectional,
	unsigned int n
) {
	for (unsigned int i = 0; i < nodes.size() - 1; i++)
		this->addMigratoryRelationship(
			nodes[i],
			nodes[i+1],
			bidirectional,
			n
		);

	this->addMigratoryRelationship(
		nodes[nodes.size()-1],
		nodes[0],
		bidirectional,
		n
	);
}

void HierarchicalEA::addMigratoryRing(
	std::string originalNode,
	std::vector<std::string> newNodeNames,
	bool bidirectional,
	unsigned int n
) {
	this->duplicateNode(originalNode, newNodeNames);
	std::vector<std::string> allNodes({originalNode});
	allNodes.insert(
		allNodes.end(),
		newNodeNames.begin(),
		newNodeNames.end()
	);

	this->addMigratoryRing(allNodes, bidirectional, n);
}

std::vector<ObjectiveFunction*> HierarchicalEA::makeApportionments(
	PopulationNode* upperNode,
	std::vector<ApportionmentFunction*> apportionments,
	std::vector<AggregationFunction*> aggregators,
	std::vector<unsigned int> tryOns
) {
	if (!this->compareVectorLengths(apportionments, aggregators))
		throw MismatchedCountsException();

	std::vector<ObjectiveFunction*> finished;
	unsigned int backupTryOns = upperNode->populationSize();
	for (unsigned int i = 0; i < apportionments.size(); i++)
		finished.push_back(new Apportionment(
			upperNode,
			apportionments[i],
			aggregators[i],
			(tryOns.empty() ? backupTryOns : tryOns[i])
		));

	return finished;
}

void HierarchicalEA::addApportionments(
	std::vector<PopulationNode*> upperNodes,
	std::vector<PopulationNode*> lowerNodes,
	std::vector<std::vector<ApportionmentFunction*>> apportionments,
	std::vector<std::vector<AggregationFunction*>> aggregators,
	std::vector<std::vector<unsigned int>> tryOns
) {
	if (!this->compareVectorLengths(
		apportionments,
		aggregators,
		tryOns,
		lowerNodes
	)) throw MismatchedCountsException();

	for (unsigned int i = 0; i < lowerNodes.size(); i++) {
		if (!this->compareVectorLengths(
			apportionments[i],
			aggregators[i],
			tryOns[i],
			upperNodes
		)) throw MismatchedCountsException();

		for (unsigned int k = 0; k < apportionments[i].size(); k++) {
			lowerNodes[i]->addObjective(new Apportionment(
				upperNodes[k],
				apportionments[i][k],
				aggregators[i][k],
				tryOns[i][k]
			));
		}
	}
}

void HierarchicalEA::addApportionments(
	std::vector<PopulationNode*> upperNodes,
	std::vector<PopulationNode*> lowerNodes,
	std::vector<unsigned int> counts,
	std::vector<std::vector<ApportionmentFunction*>> apportionments,
	std::vector<std::vector<AggregationFunction*>> aggregators,
	std::vector<std::vector<unsigned int>> tryOns
) {
	if (!this->compareVectorLengths(apportionments, aggregators, tryOns))
		throw MismatchedCountsException();

	unsigned int currentOffset = 0;
	for (unsigned int i = 0; i < upperNodes.size(); i++)
		for (unsigned int k = 0; k < counts[i]; k++) {
			lowerNodes[currentOffset]->addObjectives(
				this->makeApportionments(
					upperNodes[i],
					apportionments[currentOffset],
					aggregators[currentOffset],
					tryOns[currentOffset]
				)
			);
			currentOffset++;
		}
}

PopulationNode * HierarchicalEA::findCoevRootNode(
	std::vector<std::string> coevNodes
) {
	std::vector<PopulationNode*> realCoevNodes;
	for (unsigned int i = 0; i < coevNodes.size(); i++)
		realCoevNodes.push_back(this->getNodeByName(coevNodes[i]));

	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		PopulationNode * node = this->nodes[i];

		if (
			node->type() != NON_OPT_TYPE
			|| std::find(
				realCoevNodes.begin(),
				realCoevNodes.end(),
				node
			) != realCoevNodes.end()
		) continue;

		std::vector<Locus*> coevRootLoci = node->getCanonicalLoci();

		if (coevRootLoci.size() != realCoevNodes.size()) continue;

		bool match = true;
		for (unsigned int k = 0; k < coevRootLoci.size(); k++) {
			if (!coevRootLoci[k]->isConstructive()) {
				match = false;
				break;
			}
			PopulationNode * locusNode =
				((PopulationLocus*)coevRootLoci[i])->getNode();

			if (std::find(
				realCoevNodes.begin(),
				realCoevNodes.end(),
				locusNode
			) == realCoevNodes.end()) {
				match = false;
				break;
			}
		}
		if (!match) continue;

		return node;
	}

	throw CoevConstructionException("Unable to find coevolutionary structure from supplied nodes. Has it been set up yet?");
}

unsigned int HierarchicalEA::findHighestCoevIndex() {
	unsigned int highestIndex = 0;
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		if (boost::starts_with(
			this->nodes[i]->name(),
			OVERALL_COEV_NAME
		)) {
			std::smatch match;
			const std::string name = this->nodes[i]->name();
			if(std::regex_search(
				name.begin(),
				name.end(),
				match,
				std::regex("(\\d+)^")
			)) {
				unsigned int newIndex = boost::lexical_cast<
					unsigned int
				>(match[1]);
				if (newIndex > highestIndex)
					highestIndex = newIndex;
			}
		}
	}

	return highestIndex;
}

std::string HierarchicalEA::getNextCoevName() {
	std::stringstream ss;
	ss << OVERALL_COEV_NAME << " " << this->findHighestCoevIndex() + 1;
	return ss.str();
}
