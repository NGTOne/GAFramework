#include "FitnessFunction.h"
#include <string>
#pragma once

class RoyalRoadFitness : public FitnessFunction {
	private:

	protected:

	public:
	RoyalRoadFitness();
	int * checkFitness(GenePool ** pools, int * indexes, int genomeLength);

	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
