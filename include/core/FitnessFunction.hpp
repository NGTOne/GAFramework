#include <string>
#include "GeneNode.hpp"
#include "PropertiesList.hpp"
#pragma once

/*
* This abstract class allows us to specify whatever fitness function we like.
* This allows us to create completely generic Individuals, as the "meaning" of
* their genomes lives in an extension of this class rather than within
* themselves.
*/

class FitnessFunction {
	private:

	protected:

	public:
	virtual PropertiesList * checkFitness(GeneNode ** pools, int * indexes, int genomeLength)=0;
};

typedef FitnessFunction ComponentHeuristicFunction;
