#include "../core/EvolutionarySystem.hpp"
#include <random>
#include <string>
#pragma once

/*
* The ESGeneration model uses the (mu/rho+, lambda)-ES model, which is an
* extension of the original ES model proposed by Ingo Rechenberg et. al. in
* the 1960s.
*
* In this model, the original population, the offspring created by crossover,
* and the offspring created by mutation (which is done independently of
* crossover) are all combined into one population and sorted, with the next
* generation being the members of the combined population that are the
* most fit.
*/

class ESGeneration : public EvolutionarySystem {
	private:

	protected:

	public:

	ESGeneration(SelectionStrategy * newStrategy);

	ESGeneration(unsigned newSeed, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
