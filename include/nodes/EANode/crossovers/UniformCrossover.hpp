#ifndef NODES_EANODE_CROSSOVERS_UniformCrossover
#define NODES_EANODE_CROSSOVERS_UniformCrossover

#include "../CrossoverOperation.hpp"

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

#endif
