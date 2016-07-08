#include "pop-formulae/LocusMultiplierPopFormula.hpp"
#include "exception/ValueOutOfRangeException.hpp"

LocusMultiplierPopFormula::LocusMultiplierPopFormula(unsigned int multiplier) {
	if (multiplier == 0) throw ValueOutOfRangeException();
	this->multiplier = multiplier;
}

unsigned int LocusMultiplierPopFormula::getPopulationSize(
	unsigned int numLoci
) {
	return numLoci * this->multiplier;
}
