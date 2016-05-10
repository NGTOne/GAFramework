#include "core/migration/TranslationFunction.hpp"

Genome * TranslationFunction::translate(Genome * target) {
	return new Genome(target, false);
}

bool TranslationFunction::isNull() {
	return false;
}
