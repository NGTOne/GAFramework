#include "../core/PopulationFormula.hpp"
#pragma once

class LocusMultiplierPopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int multiplier;

	public:
	LocusMultiplierPopFormula(unsigned int multiplier);
	unsigned int getPopulationSize(std::vector<Locus*> loci);
};
