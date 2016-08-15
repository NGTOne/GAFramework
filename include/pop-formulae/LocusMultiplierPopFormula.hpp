#ifndef POP_FORMULAE_LocusMultiplierPopFormula
#define POP_FORMULAE_LocusMultiplierPopFormula

#include "../core/PopulationFormula.hpp"

class LocusMultiplierPopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int multiplier;

	public:
	LocusMultiplierPopFormula(unsigned int multiplier);
	unsigned int getPopulationSize(std::vector<Locus*> loci);
};

#endif
