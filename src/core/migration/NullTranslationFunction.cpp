#include "core/migration/NullTranslationFunction.hpp"

Individual * NullTranslationFunction::translate(Individual * target) {
	return NULL;
}

bool NullTranslationFunction::isNull() {
	return true;
}
