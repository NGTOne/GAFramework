#include "Locus.hpp"
#include <vector>
#pragma once

class PopulationFormula {
	private:

	protected:

	public:
	virtual ~PopulationFormula();

	// I don't like it being this simple, but I can't think of how to
	// extend it
	// TODO: Think of additional possible parameters
	virtual unsigned int getPopulationSize(std::vector<Locus*> loci)=0;
};
