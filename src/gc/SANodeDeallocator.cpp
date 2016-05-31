#include "gc/SANodeDeallocator.hpp"
#include "nodes/SANode/SANode.hpp"
#include <set>

SANodeDeallocator::SANodeDeallocator() {}
SANodeDeallocator::~SANodeDeallocator() {}

bool SANodeDeallocator::canDeleteNode(PopulationNode * node) {
	return node->type() == SA_TYPE;
}

void SANodeDeallocator::deleteNodes() {
	set<TemperatureSchedule*> schedules;
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		schedules.insert(((SANode*)this->nodes[i])->getSchedule());
		delete(this->nodes[i]);
	}

	this->clearSet<TemperatureSchedule*>(schedules);
}
