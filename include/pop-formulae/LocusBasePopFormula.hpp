#ifndef POP_FORMULAE_LocusBasePopFormula
#define POP_FORMULAE_LocusBasePopFormula

#include "../core/PopulationFormula.hpp"

class LocusBasePopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int exponent;

	public:
	LocusBasePopFormula(unsigned int exponent);
	unsigned int getPopulationSize(std::vector<Locus*> loci);
};

#endif
