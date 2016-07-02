#include "../nodes/EANode/CrossoverOperation.hpp"
#pragma once

class UniformCrossover : public CrossoverOperation {
	private:

	protected:
	
	public:
	UniformCrossover();
	UniformCrossover(unsigned int numOffspring);
	UniformCrossover(unsigned int numOffspring, unsigned int seed);

	std::vector<std::tuple<
		std::vector<unsigned int>,
		std::vector<Locus*>
	>> crossOver(std::vector<Genome*> genomes);
};
