#include "Individual.h"
#include "SelectionStrategy.h"
#include "GenerationModel.h"
#include <random>
#include <string>
#pragma once

class ESGeneration : GenerationModel {
	private:

	protected:

	public:

	ESGeneration(double newCrossoverRate, int newNumElites, SelectionStrategy * newStrategy);

	ESGeneration(unsigned newSeed, double newCrossoverRate, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize)=0;
};
