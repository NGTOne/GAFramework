#include "core/EndCondition.hpp"

EndCondition::EndCondition() {}

EndCondition::~EndCondition() {}

bool EndCondition::checkSolution(Genome * target, float targetFitness) {
	return false;
}

void EndCondition::registerInternalObjects(NodeGarbageCollector & collector) {}
