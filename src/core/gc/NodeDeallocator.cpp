#include "core/gc/NodeDeallocator.hpp"

NodeDeallocator::NodeDeallocator() {}
NodeDeallocator::~NodeDeallocator() {}

void NodeDeallocator::registerNode(PopulationNode * node) {
	this->nodes.push_back(node);
}
