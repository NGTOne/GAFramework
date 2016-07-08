#include "pop-formulae/LocusExponentPopFormula.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <cmath>

LocusExponentPopFormula::LocusExponentPopFormula(unsigned int base) {
	if (base <= 1) throw ValueOutOfRangeException();
	this->base = base;
}

unsigned int LocusExponentPopFormula::getPopulationSize(unsigned int numLoci) {
	return std::pow(this->base, numLoci);
}
