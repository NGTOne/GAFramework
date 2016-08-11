#include "nodes/NonOptimizingNode.hpp"
#include <sstream>

NonOptimizingNode::NonOptimizingNode(
	unsigned int populationSize,
	std::vector<Locus*> loci,
	std::vector<ObjectiveFunction*> objectives,
	ToStringFunction* populationToString,
	std::vector<EndCondition*> conditions,
	std::string nodeName
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

PopulationNode* NonOptimizingNode::duplicate(std::string newNodeName) {
	return new NonOptimizingNode(
		this->populationSize(),
		this->getCanonicalLoci(),
		this->getObjectives(),
		this->getToString(),
		this->getConditions(),
		newNodeName
	);
}
