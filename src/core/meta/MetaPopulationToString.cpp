#include "core/meta/MetaPopulationToString.hpp"
#include "core/meta/BlanketResolver.hpp"

MetaPopulationToString::MetaPopulationToString(
	ToStringFunction * flattenedToString
) {
	this->flattenedToString = flattenedToString;
}

std::string MetaPopulationToString::toString(Genome * genome) {
	Genome resolved = BlanketResolver::resolveBlanket(genome);
	return this->flattenedToString->toString(&resolved);
}
