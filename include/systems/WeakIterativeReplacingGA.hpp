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

class WeakIterativeReplacingGA : public ReplacingGA {
	private:

	protected:

	public:
	WeakIterativeReplacingGA(SelectionStrategy * newStrategy);
	WeakIterativeReplacingGA(
		unsigned newSeed,
		SelectionStrategy * newStrategy
	);

	Individual ** breedMutateSelect(
		Individual ** initialPopulation,
		int * populationFitnesses,
		int populationSize
	);
};
