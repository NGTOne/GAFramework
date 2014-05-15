#include "Individual.hpp"
#include "SelectionStrategy.hpp"
#include "GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

class GAGeneration : public GenerationModel {
	private:

	protected:

	public:

	GAGeneration(int newNumElites, SelectionStrategy * newStrategy);

	GAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
