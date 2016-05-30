#include "core/gc/NodeGarbageCollector.hpp"
#include "gc/PopulationNodeDeallocator.hpp"
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
	// Must come first
	this->deallocators.push_back(new PopulationNodeDeallocator());
	this->deallocators.push_back(new NonOptimizingNodeDeallocator());
	this->deallocators.push_back(new SANodeDeallocator());
	this->deallocators.push_back(new EANodeDeallocator());
}

NodeGarbageCollector::~NodeGarbageCollector() {
	for (unsigned int i = 0; i < this->deallocators.size(); i++)
		delete(this->deallocators[i]);
}

void NodeGarbageCollector::deleteNodes(std::vector<PopulationNode*> nodes) {
	for (unsigned int i = 0; i < nodes.size(); i++)
		for (unsigned int k = 0; k < this->deallocators.size(); k++)
			if (this->deallocators[k]->canDeleteNode(nodes[i]))
				this->deallocators[k]->registerNode(nodes[i]);

	for (unsigned int i = 0; i < this->deallocators.size(); i++)
		this->deallocators[i]->deleteNodes();
}
