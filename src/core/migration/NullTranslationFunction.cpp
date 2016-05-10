#include "core/migration/NullTranslationFunction.hpp"

Genome * NullTranslationFunction::translate(Genome * target) {
	return NULL;
}

bool NullTranslationFunction::isNull() {
	return true;
}
