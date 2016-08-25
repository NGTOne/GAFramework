#ifndef NODES_EANODE_CROSSOVERS_UniformCrossover
#define NODES_EANODE_CROSSOVERS_UniformCrossover

#include "../CrossoverOperation.hpp"
#include <vector>

class UniformCrossover : public CrossoverOperation {
	private:

	protected:
	std::vector<double> parentCrossoverProbabilities;
	std::vector<GenomeTemplate> crossOver(
		std::vector<GenomeTemplate> parents
	);
	
	public:
	UniformCrossover(
		std::vector<double> parentCrossoverProbabilities =
			std::vector<double>()
	);
	UniformCrossover(
		unsigned int numOffspring,
		std::vector<double> parentCrossoverProbabilities =
			std::vector<double>()
	);

	std::string toString();
};

#endif
