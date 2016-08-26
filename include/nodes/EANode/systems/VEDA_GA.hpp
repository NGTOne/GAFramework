#ifndef NODES_EANODE_SYSTEMS_VEDA_GA
#define NODES_EANODE_SYSTEMS_VEDA_GA

#include "GA.hpp"

class VEDA_GA: public GA {
	private:

	protected:

	public:
	VEDA_GA(
		unsigned int numElites,
		bool randomElitePlacement,
		SelectionStrategy* strategy,
		CrossoverOperation* cross
	);
	VEDA_GA(
		unsigned int numElites,
		SelectionStrategy* strategy,
		CrossoverOperation* cross
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};

#endif
