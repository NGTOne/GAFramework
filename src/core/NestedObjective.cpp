#include "core/NestedObjective.hpp"
#include "core/utils/HierGC.hpp"

NestedObjective::NestedObjective(ObjectiveFunction * innerObjective) {
	this->innerObjective = innerObjective;
}

void NestedObjective::registerInternalObjects() {
	ObjectiveFunction::registerInternalObjects();
	HierGC::registerObject(this->innerObjective);
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
