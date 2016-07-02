#include "core/migration/NullTranslationFunction.hpp"

GenomeTemplate NullTranslationFunction::translate(Genome * target) {
	return GenomeTemplate();
}

Genome * NullTranslationFunction::createTranslatedGenome(
	Genome * target,
	std::string targetNode
) {
	return NULL;
}

bool NullTranslationFunction::isNull() {
	return true;
}
