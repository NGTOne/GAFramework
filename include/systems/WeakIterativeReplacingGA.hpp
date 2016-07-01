#include "ReplacingGA.hpp"
#include <vector>
#pragma once

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
	WeakIterativeReplacingGA(SelectionStrategy * strategy);
	WeakIterativeReplacingGA(
		SelectionStrategy * strategy,
		unsigned seed
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float> & populationFitnesses,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};
