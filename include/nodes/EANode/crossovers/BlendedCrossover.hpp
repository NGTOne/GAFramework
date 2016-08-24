#ifndef NODES_EANODE_CROSSOVERS_BlendedCrossover
#define NODES_EANODE_CROSSOVERS_BlendedCrossover

#include "../CrossoverOperation.hpp"

class BlendedCrossover : public CrossoverOperation {
	private:

	protected:
	std::vector<GenomeTemplate> crossOver(
		std::vector<GenomeTemplate> parents
	);
	
	public:
	BlendedCrossover();
	std::string toString();
};

#endif
