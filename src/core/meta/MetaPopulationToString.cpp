#include "core/meta/MetaPopulationToString.hpp"

MetaPopulationToString::MetaPopulationToString(
	ToStringFunction * flattenedToString
) {
	this->flattenedToString = flattenedToString;
}

std::string MetaPopulationToString::toString(Genome * genome) {
	Genome resolved = this->resolveBlanket(genome);
	return this->flattenedToString->toString(&resolved);
}
