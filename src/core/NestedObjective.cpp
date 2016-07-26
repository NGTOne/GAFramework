#include "core/NestedObjective.hpp"

NestedObjective::NestedObjective(ObjectiveFunction * innerObjective) {
	this->innerObjective = innerObjective;
}

void NestedObjective::registerInternalObjects(
	NodeGarbageCollector & collector
) {
	ObjectiveFunction::registerInternalObjects(collector);
	collector.registerObject(this->innerObjective);
}

bool NestedObjective::isNested() {
	return true;
}

float NestedObjective::checkInnerFitness(Genome * target) {
	return this->innerObjective->checkFitness(target);
}

std::vector<ObjectiveFunction*> NestedObjective::getInner() {
	std::vector<ObjectiveFunction*> inner;
	if (this->innerObjective->isNested())
		inner = ((NestedObjective*)this->innerObjective)->getInner();
	inner.push_back(this->innerObjective);

	return inner;
}
