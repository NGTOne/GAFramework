#include "core/ObjectiveFunction.hpp"

ObjectiveFunction::~ObjectiveFunction() {}

bool ObjectiveFunction::isApportioning() {
	return false;
}

bool ObjectiveFunction::isNested() {
	return false;
}

void ObjectiveFunction::registerInternalObjects(
	NodeGarbageCollector & collector
) {}
