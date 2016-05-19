#include "ReplacingGA.hpp"
#include <vector>
#pragma once

/*
* The ReplacingGA model represents a "classical" GA model,
* similar to that proposed by John Holland in the 1970s, but where the
* offspring may (or may not) replace their parents at the exact same locations
* in the population.
*/

class StrongIterativeReplacingGA : public ReplacingGA {
	private:

	protected:
	bool scramble;

	void scramblePopulation(
		std::vector<Genome*> & population,
		std::vector<int> & fitnesses
	);

	public:
	StrongIterativeReplacingGA(SelectionStrategy * strategy);
	StrongIterativeReplacingGA(
		SelectionStrategy * strategy,
		unsigned seed
	);
	StrongIterativeReplacingGA(
		SelectionStrategy * strategy,
		bool scramble
	);
	StrongIterativeReplacingGA(
		SelectionStrategy * strategy,
		bool scramble,
		unsigned seed
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<int> & populationFitness,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		std::vector<ObjectiveFunction*> objectives
	);
};
