#include "core/eval/ToStringFunction.hpp"

ToStringFunction::~ToStringFunction() {}

bool ToStringFunction::isNested() {
	return false;
}

bool ToStringFunction::isHierarchical() {
	return false;
}
