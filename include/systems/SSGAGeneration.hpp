#include "../core/EvolutionarySystem.hpp"
#include "niching/NichingStrategy.hpp"
#include <random>
#include <string>
#pragma once

/*
* The SSGAGeneration model uses the steady-state GA model, in which one pair
* of parents is directly replaced by their offspring in each generation. For
* this reason, it is much slower than other models, but can yield results
* that may not appear using them.
*/

class SSGAGeneration : public EvolutionarySystem {
	private:

	protected:
	NichingStrategy * niching;

	public:

	SSGAGeneration(SelectionStrategy * newStrategy);
	SSGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy);
	SSGAGeneration(SelectionStrategy * newStrategy, NichingStrategy * newNiching);
	SSGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy, NichingStrategy * newNiching);
	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
