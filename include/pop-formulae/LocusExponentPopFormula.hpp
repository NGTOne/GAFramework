#include "../core/PopulationFormula.hpp"
#pragma once

class LocusExponentPopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int base;

	public:
	LocusExponentPopFormula(unsigned int base);
	unsigned int getPopulationSize(std::vector<Locus*> loci);
};
