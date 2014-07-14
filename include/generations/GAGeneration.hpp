#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

//This generation model is a standard genetic algorithm (GA), which works by
//generating a population of offspring, separate from the parents, and
//discarding the parents afterwards (with the possible exception of a few
//elites). For odd-numbered populations, the final member is the offspring
//of two parents as normal, with its sibling being discarded.
class GAGeneration : public GenerationModel {
	private:

	protected:
	int numElites;

	public:

	GAGeneration(int newNumElites, SelectionStrategy * newStrategy);

	GAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
