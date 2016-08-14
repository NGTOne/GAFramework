#include "core/eval/ObjectiveFunction.hpp"

ObjectiveFunction::~ObjectiveFunction() {}

bool ObjectiveFunction::isApportioning() {
	return false;
}

bool ObjectiveFunction::isNested() {
	return false;
}
