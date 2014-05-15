#include "Individual.hpp"
#include "SelectionStrategy.hpp"
#include "GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

class SSGAGeneration : public GenerationModel {
	private:

	protected:

	public:

	SSGAGeneration(int newNumElites, SelectionStrategy * newStrategy);

	SSGAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
