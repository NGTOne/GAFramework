#ifndef NODES_EANODE_CROSSOVERS_BlendedCrossover
#define NODES_EANODE_CROSSOVERS_BlendedCrossover

#include "../CrossoverOperation.hpp"

class BlendedCrossover : public CrossoverOperation {
	private:

	protected:
	std::vector<double> parentWeights;

	std::vector<GenomeTemplate> crossOver(
		std::vector<GenomeTemplate> parents
	);
	
	public:
	BlendedCrossover(
		std::vector<double> parentWeights = std::vector<double>()
	);
	std::string toString();
};

#endif
