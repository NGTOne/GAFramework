#include "CrossoverOperation.h"
#pragma once

class UniformCrossover : public CrossoverOperation {
	private:

	protected:

	double crossoverRate;
	
	public:
	
	UniformCrossover(double crossoverChance);
	UniformCrossover(double crossoverChance, unsigned newSeed);

	Genome ** crossOver(Genome * firstGenome, Genome * secondGenome);

	std::string toString();
};
