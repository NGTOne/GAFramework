#include "core/migration/TranslationFunction.hpp"
#include "core/Individual.hpp"

Individual * TranslationFunction::translate(Individual * target) {
	return target->deepCopy();
}

bool TranslationFunction::isNull() {
	return false;
}
