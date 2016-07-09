#include "../core/PopulationFormula.hpp"
#pragma once

class ConstructiveLocusCountPopFormula: public PopulationFormula {
	private:

	protected:
	unsigned int multiplier;

	public:
	unsigned int getPopulationSize(std::vector<Locus*> loci);
};
