#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

//This generation model represents the "steady-state GA" model, in which
//population replacements happen one-to-one, in-situ. Rather than generating
//a new population of individuals, replacement happens immediately after
//crossover/mutation, with the offspring taking the place of their parents.
//This particular implementation uses local elitism (in which replacement
//only occurs if the offspring are inferior to the parents).
class SSGAGeneration : public GenerationModel {
	private:

	protected:

	public:

	SSGAGeneration(SelectionStrategy * newStrategy);

	SSGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
