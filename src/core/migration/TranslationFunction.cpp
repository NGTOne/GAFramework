#include "core/migration/TranslationFunction.hpp"

GenomeTemplate TranslationFunction::translate(GenomeTemplate target) {
	return GenomeTemplate(target.getGenes());
}

Genome* TranslationFunction::createTranslatedGenome(
	Genome* target,
	std::string targetNode
) {
	return new Genome(this->translate(target->getTemplate()), targetNode);
}

bool TranslationFunction::isNull() {
	return false;
}
