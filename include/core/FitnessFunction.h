//This is an abstract class for fitness functions - should be extended as
//necessary, with one subclass per "species" of individual

#include <string>
#include "GenePool.h"
#pragma once

class FitnessFunction {
	private:

	protected:

	public:
	int checkFitness(GenePool pools[], int indexes[], int genomeLength);
	std::string toString(GenePool pools[], int indexes[], int genomeLength);
};
