#include "core/migration/NullTranslationFunction.hpp"

GenomeTemplate NullTranslationFunction::translate(GenomeTemplate target) {
	return GenomeTemplate();
}

Genome* NullTranslationFunction::createTranslatedGenome(
	Genome* target,
	std::string targetNode
) {
	return NULL;
}

bool NullTranslationFunction::isNull() {
	return true;
}
