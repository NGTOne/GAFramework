#ifndef NODES_EANODE_SYSTEMS_NICHING_Crowding
#define NODES_EANODE_SYSTEMS_NICHING_Crowding

#include "NichingStrategy.hpp"

class Crowding : public NichingStrategy {
	private:

	protected:

	public:
	std::vector<unsigned int> getIndices(
		std::vector<Genome*> initialPopulation,
		std::vector<Genome*> newPopulation
	);
};

#endif
