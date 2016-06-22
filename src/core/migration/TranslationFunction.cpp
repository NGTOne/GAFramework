#include "core/migration/TranslationFunction.hpp"

std::tuple<
	std::vector<unsigned int>,
	std::vector<Locus*>
> TranslationFunction::translate(Genome * target) {
	return std::make_tuple(target->getGenome(), target->getLoci());
}

Genome * TranslationFunction::createTranslatedGenome(
	Genome * target,
	std::string targetNode
) {
	std::vector<unsigned int> newGenes;
	std::vector<Locus*> newLoci;
	std::tie(newGenes, newLoci) = this->translate(target);
	return new Genome(newGenes, newLoci, targetNode);
}

bool TranslationFunction::isNull() {
	return false;
}
