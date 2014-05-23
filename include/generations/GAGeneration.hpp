#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

class GAGeneration : public GenerationModel {
	private:

	protected:
	int numElites;

	public:

	GAGeneration(int newNumElites, SelectionStrategy * newStrategy);

	GAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
