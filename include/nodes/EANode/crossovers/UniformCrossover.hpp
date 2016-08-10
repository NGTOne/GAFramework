#include "../CrossoverOperation.hpp"
#pragma once

class UniformCrossover : public CrossoverOperation {
	private:

	protected:
	std::vector<GenomeTemplate> crossOver(
		std::vector<GenomeTemplate> parents
	);
	
	public:
	UniformCrossover();
	UniformCrossover(unsigned int numOffspring);

	std::string toString();
};
