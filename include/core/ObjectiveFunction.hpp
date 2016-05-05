#include <string>
#include "Genome.hpp"
#include "PropertiesList.hpp"
#pragma once

/*
* This abstract class allows us to specify whatever fitness function we like.
* This allows us to create completely generic Individuals, as the "meaning" of
* their genomes lives in an extension of this class rather than within
* themselves.
*/

class ObjectiveFunction {
	private:

	protected:

	public:
	virtual PropertiesList * checkFitness(Genome * genome)=0;
};
