#include "FitnessFunction.h"
#include <string>
#pragma once

class HierOneMaxFitness : public FitnessFunction {
	private:

	protected:

	public:
	HierOneMaxFitness();
	int checkFitness(GenePool ** pools, int * indexes, int genomeLength);

	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
