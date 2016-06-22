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
	return new Genome(this->translate(target), targetNode);
}

bool TranslationFunction::isNull() {
	return false;
}
