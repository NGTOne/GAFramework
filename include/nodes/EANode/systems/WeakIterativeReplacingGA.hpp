#ifndef NODES_EANODE_SYSTEMS_WeakIterativeReplacingGA
#define NODES_EANODE_SYSTEMS_WeakIterativeReplacingGA

#include "ReplacingGA.hpp"
#include <vector>

/*
* The ReplacingGA model represents a "classical" GA model,
* similar to that proposed by John Holland in the 1970s, but where the
* offspring may (or may not) replace their parents at the exact same locations
* in the population.
*/

class WeakIterativeReplacingGA : public ReplacingGA {
	private:

	protected:

	public:
	WeakIterativeReplacingGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<Fitness>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};

#endif
