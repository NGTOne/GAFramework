#include "ReplacingGA.hpp"
#include <random>
#include <string>
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

	void scramblePopulation(Individual ** population, int populationSize);

	public:
	StrongIterativeReplacingGA(SelectionStrategy * newStrategy);
	StrongIterativeReplacingGA(
		unsigned newSeed,
		SelectionStrategy * newStrategy
	);
	StrongIterativeReplacingGA(
		bool scramble,
		SelectionStrategy * strategy
	);
	StrongIterativeReplacingGA(
		unsigned seed,
		bool scramble,
		SelectionStrategy * strategy
	);

	Individual ** breedMutateSelect(
		Individual ** initialPopulation,
		int * populationFitnesses,
		int populationSize
	);
};
