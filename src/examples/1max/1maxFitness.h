#include "FitnessFunction.h"
#include <string>
#pragma once

class OneMaxFitness : public FitnessFunction {
	private:

	protected:

	public:
	OneMaxFitness();
	int checkFitness(GenePool ** pools, int * indexes, int genomeLength);

	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
