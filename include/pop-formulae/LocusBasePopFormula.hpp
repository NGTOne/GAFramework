#include "../core/PopulationFormula.hpp"
#pragma once

class LocusBasePopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int exponent;

	public:
	LocusBasePopFormula(unsigned int exponent);
	unsigned int getPopulationSize(unsigned int numLoci);
};
