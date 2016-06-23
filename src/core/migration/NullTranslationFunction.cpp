#include "core/migration/NullTranslationFunction.hpp"

std::tuple<
	std::vector<unsigned int>,
	std::vector<Locus*>
> NullTranslationFunction::translate(Genome * target) {
	return std::make_tuple(
		std::vector<unsigned int>(),
		std::vector<Locus*>()
	);
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
