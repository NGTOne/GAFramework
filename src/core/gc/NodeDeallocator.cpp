#include "core/gc/NodeDeallocator.hpp"

NodeDeallocator::NodeDeallocator() {}
NodeDeallocator::~NodeDeallocator() {}

void NodeDeallocator::registerNode(PopulationNode * node) {
	this->nodes.push_back(node);
}

template <typename T>
void clearSet(typename std::set<T> target) {
	std::vector<T> targetVector(target.begin(), target.end());

	for (int i = 0; i < targetVector.size(); i++)
		delete(targetVector[i]);
}
