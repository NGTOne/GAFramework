#ifndef POP_FORMULAE_ConstructiveLocusCountPopFormula
#define POP_FORMULAE_ConstructiveLocusCountPopFormula

#include "../core/PopulationFormula.hpp"

class ConstructiveLocusCountPopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int multiplier;

	public:
	unsigned int getPopulationSize(std::vector<Locus*> loci);
};

#endif
