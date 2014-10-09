#include "../core/CrossoverOperation.hpp"
#pragma once

/*
* The uniform crossover operator randomly generates a bitwise mask, and then
* crosses over only the genes that are masked.
*
* EXAMPLE:
* Mask:        01110101
* Parent 1:    ABBBDCCB
* Parent 2:    BBCDABDA
* Offspring 1: ABCDDBCA
* Offspring 2: BBBBACDB
*/

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
