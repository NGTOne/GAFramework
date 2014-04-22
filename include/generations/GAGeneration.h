#include "Individual.h"
#include "SelectionStrategy.h"
#include "GenerationModel.h"
#include <random>
#include <string>
#pragma once

class GAGeneration : GenerationModel {
	private:

	protected:

	public:

	GAGeneration(int newNumElites, SelectionStrategy * newStrategy);

	GAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize)=0;
};
