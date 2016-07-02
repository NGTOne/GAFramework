#include "../nodes/EANode/CrossoverOperation.hpp"
#pragma once

class UniformCrossover : public CrossoverOperation {
	private:

	protected:
	std::vector<GenomeTemplate> crossOver(
		std::vector<Genome*> genomes
	);
	
	public:
	UniformCrossover();
	UniformCrossover(unsigned int numOffspring);
	UniformCrossover(unsigned int numOffspring, unsigned int seed);

	std::string toString();
};
