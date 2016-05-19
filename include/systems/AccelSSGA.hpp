#include "SSGA.hpp"
#include "niching/NichingStrategy.hpp"
#include <vector>
#pragma once

/*
* The "Accelerated SSGA" model uses the steady-state GA model, in which one pair
* of parents is directly replaced by their offspring in each generation. For
* this reason, it is much slower than other models, but can yield results
* that may not appear using them.
*
* The big difference between this and "standard" SSGA is that it performs
* n/2 operations (where n is the population size) rather than just 1 operation
* per generation
*/

class AccelSSGA : public SSGA {
	private:

	protected:

	public:
	AccelSSGA(SelectionStrategy * strategy);
	AccelSSGA(SelectionStrategy * strategy, unsigned seed);
	AccelSSGA(
		SelectionStrategy * strategy,
		NichingStrategy * niching
	);

	AccelSSGA(
		SelectionStrategy * strategy,
		NichingStrategy * niching,
		unsigned seed
	);

	virtual std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<int> & populationFitnesses,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		std::vector<ObjectiveFunction*> objectives
	);
};
