#include "core/migration/TranslationFunction.hpp"

GenomeTemplate TranslationFunction::translate(Genome * target) {
	return GenomeTemplate(target->getGenome(), target->getLoci());
}

Genome * TranslationFunction::createTranslatedGenome(
	Genome * target,
	std::string targetNode
) {
	return new Genome(this->translate(target), targetNode);
}

bool TranslationFunction::isNull() {
	return false;
}
