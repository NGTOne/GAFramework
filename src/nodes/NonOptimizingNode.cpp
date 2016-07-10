#include "nodes/NonOptimizingNode.hpp"
#include <sstream>

using namespace std;

NonOptimizingNode::NonOptimizingNode(
	unsigned int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string nodeName
) : PopulationNode(
	populationSize,
	loci,
	objectives,
	populationToString,
	conditions,
	nodeName
) {}

void NonOptimizingNode::nextIteration() {
	if (!done()) evaluateFitnesses();
}

std::vector<Genome*> NonOptimizingNode::getNextPopulation() {
	return this->population;
}

node_type_t NonOptimizingNode::type() {
	return NON_OPT_TYPE;
}

PopulationNode * NonOptimizingNode::duplicate(std::string newNodeName) {
	return new NonOptimizingNode(
		this->populationSize(),
		this->getCanonicalLoci(),
		this->getObjectives(),
		this->getToString(),
		this->getConditions(),
		newNodeName
	);
}
