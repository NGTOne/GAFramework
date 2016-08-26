#ifndef NODES_EANODE_CROSSOVERS_UniformCrossover
#define NODES_EANODE_CROSSOVERS_UniformCrossover

#include "../CrossoverOperation.hpp"
#include <vector>

class UniformCrossover : public CrossoverOperation {
	private:
	void init(std::vector<double> parentProbabilities);

	protected:
	std::vector<double> parentProbabilities;
	std::vector<GenomeTemplate> crossOver(
		std::vector<GenomeTemplate> parents
	);
	
	public:
	UniformCrossover(
		std::vector<double> parentProbabilities = std::vector<double>()
	);
	UniformCrossover(
		unsigned int numOffspring,
		std::vector<double> parentProbabilities = std::vector<double>()
	);

	std::string toString();
};

#endif
