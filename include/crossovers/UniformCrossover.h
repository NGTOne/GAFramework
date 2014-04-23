#include "CrossoverOperation.h"
#pragma once

class UniformCrossover : public CrossoverOperation {
	private:

	protected:

	double crossoverRate;
	
	public:
	
	UniformCrossover(double crossoverChance);
	UniformCrossover(double crossoverChance, unsigned newSeed);

	int ** crossOver(int firstGenome[], int secondGenome[], int firstGenomeLength, int secondGenomeLength);

};
