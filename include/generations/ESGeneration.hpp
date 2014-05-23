#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

class ESGeneration : public GenerationModel {
	private:

	protected:

	public:

	ESGeneration(SelectionStrategy * newStrategy);

	ESGeneration(unsigned newSeed, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
