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

bool MetaPopulationToString::isNested() {
	return true;
}

std::vector<ToStringFunction*> MetaPopulationToString::getNested() {
	std::vector<ToStringFunction*> inner;
	if (this->flattenedToString->isNested())
		inner = ((MetaPopulationToString*)this->flattenedToString)
			->getNested();
	inner.push_back(this->flattenedToString);
	return inner;
}
