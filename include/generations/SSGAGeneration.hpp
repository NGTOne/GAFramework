#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

class SSGAGeneration : public GenerationModel {
	private:

	protected:

	public:

	SSGAGeneration(SelectionStrategy * newStrategy);

	SSGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
