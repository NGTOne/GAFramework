#include "Individual.h"
#include "SelectionStrategy.h"
#include "GenerationModel.h"
#include <random>
#include <string>
#pragma once

class SSGAGeneration : GenerationModel {
	private:

	protected:

	public:

	SSGAGeneration(int newNumElites, SelectionStrategy * newStrategy);

	SSGAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize)=0;
};
