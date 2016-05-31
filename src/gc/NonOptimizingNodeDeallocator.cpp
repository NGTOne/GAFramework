#include "gc/NonOptimizingNodeDeallocator.hpp"
#include "nodes/NonOptimizingNode.hpp"

NonOptimizingNodeDeallocator::NonOptimizingNodeDeallocator() {}
NonOptimizingNodeDeallocator::~NonOptimizingNodeDeallocator() {}

bool NonOptimizingNodeDeallocator::canDeleteNode(PopulationNode * node) {
	return node->type() == NON_OPT_TYPE;
}

void NonOptimizingNodeDeallocator::deleteNodes() {
	for (unsigned int i = 0; i < this->nodes.size(); i++)
		delete(this->nodes[i]);
}
