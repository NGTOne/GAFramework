#ifndef POP_FORMULAE_LocusExponentPopFormula
#define POP_FORMULAE_LocusExponentPopFormula

#include "../core/PopulationFormula.hpp"

class LocusExponentPopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int base;

	public:
	LocusExponentPopFormula(unsigned int base);
	unsigned int getPopulationSize(std::vector<Locus*> loci);
};

#endif
