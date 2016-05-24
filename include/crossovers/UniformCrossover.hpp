#include "../nodes/EANode/CrossoverOperation.hpp"
#pragma once

class UniformCrossover : public CrossoverOperation {
	private:

	protected:
	
	public:
	UniformCrossover();
	UniformCrossover(unsigned int numOffspring);
	UniformCrossover(unsigned int numOffspring, unsigned seed);

	std::vector<Genome*> crossOver(std::vector<Genome*> genomes);
};
