#include "core/gc/NodeGarbageCollector.hpp"
#include <algorithm>

NodeGarbageCollector::NodeGarbageCollector() {}

NodeGarbageCollector::~NodeGarbageCollector() {}

void NodeGarbageCollector::cleanUp() {
	for (auto object : this->objects) delete(object);
}

void NodeGarbageCollector::registerObject(EABehaviourObject * object) {
	object->registerInternalObjects(*this);
	this->objects.insert(object);
}
