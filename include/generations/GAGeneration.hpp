#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

/*
* The GAGeneration model reflects the "classic" GA, as popularized by the work
* of John Holland in the 1970s.
*
* In this model, a few elites (the best of the previous generation) are
* selected and allowed to survive to the next generation. The remainder of
* the next generation is filled in with new offspring that are created by a
* combination of crossover and mutation.
*/

class GAGeneration : public GenerationModel {
	private:

	protected:
	int numElites;

	public:

	GAGeneration(int newNumElites, SelectionStrategy * newStrategy);

	GAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
