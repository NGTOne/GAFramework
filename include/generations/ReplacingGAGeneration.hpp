#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

/*
* The ReplacingGAGeneration model represents a "classical" GA model,
* similar to that proposed by John Holland in the 1970s, but where the
* offspring may (or may not) replace their parents at the exact same locations
* in the population.
*/

class ReplacingGAGeneration : public GenerationModel {
	private:
	double replacementRate;

	protected:
	void removeUnusedIndividuals(Individual ** initialPopulation, Individual ** newPopulation, int populationSize);
	bool inPopulation(Individual * target, Individual ** population, int populationSize);

	public:
	ReplacingGAGeneration(SelectionStrategy * newStrategy, double newReplacementRate);
	ReplacingGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy, double newReplacementRate);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
