#include "core/migration/TranslationFunction.hpp"

Genome * TranslationFunction::translate(Genome * target) {
	return new Genome(target);
}

bool TranslationFunction::isNull() {
	return false;
}
