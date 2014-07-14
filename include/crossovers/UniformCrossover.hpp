#include "../core/CrossoverOperation.hpp"
#pragma once

//Uniform crossover is, in effect, a "bitwise" crossover operator. Each gene
//in the genome decides randomly whether it will be swapped with its
//correspondent gene in the other parent.
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
