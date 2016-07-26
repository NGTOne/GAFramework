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
		std::vector<float> & fitnesses
	);

	public:
	StrongIterativeReplacingGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);
	StrongIterativeReplacingGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		unsigned int seed
	);
	StrongIterativeReplacingGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		bool scramble
	);
	StrongIterativeReplacingGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		bool scramble,
		unsigned int seed
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float> & populationFitness,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};
