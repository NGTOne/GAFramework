#include "core/gc/NodeGarbageCollector.hpp"
#include "gc/NonOptimizingNodeDeallocator.hpp"
#include "gc/SANodeDeallocator.hpp"
#include "gc/EANodeDeallocator.hpp"

/*
* A bit of WTF here - we hand-create one of each of the different deallocator
* types, to handle the specific node types
*
* Needs to be updated as new node types and their corresponding deallocators are
* added
*/
NodeGarbageCollector::NodeGarbageCollector() {
	this->deallocators.push_back(new NonOptimizingNodeDeallocator());
	this->deallocators.push_back(new SANodeDeallocator());
	this->deallocators.push_back(new EANodeDeallocator());
}

NodeGarbageCollector::~NodeGarbageCollector() {
	for (int i = 0; i < this->deallocators.size(); i++)
		delete(this->deallocators[i]);
}

void NodeGarbageCollector::deleteNodes(std::vector<PopulationNode*> nodes) {
	for (int i = 0; i < nodes.size(); i++)
		for (int k = 0; k < this->deallocators.size(); k++)
			if (this->deallocators[k]->canDeleteNode(nodes[i])) {
				this->deallocators[k]->registerNode(nodes[i]);
				break;
			}

	for (int i = 0; i < this->deallocators.size(); i++)
		this->deallocators[i]->deleteNodes();
}
