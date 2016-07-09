#include "pop-formulae/LocusBasePopFormula.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <cmath>

LocusBasePopFormula::LocusBasePopFormula(unsigned int exponent) {
	if (exponent <= 1) throw ValueOutOfRangeException();
	this->exponent = exponent;
}

unsigned int LocusBasePopFormula::getPopulationSize(std::vector<Locus*> loci) {
	return std::pow(loci.size(), this->exponent);
}
