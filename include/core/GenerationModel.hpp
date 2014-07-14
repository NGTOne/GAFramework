#include "Individual.hpp"
#include "SelectionStrategy.hpp"
#include <random>
#include <string>
#pragma once

//This abstract class allows us to define different "generation models" - i.e.
//how a GA behaves during each generation. Examples of generation models
//include GA and ES.
class GenerationModel {
	private:

	protected:
	unsigned seed;
	std::mt19937 generator;
	SelectionStrategy * myStrategy;

	public:

	GenerationModel(SelectionStrategy * newStrategy);

	GenerationModel(unsigned newSeed, SelectionStrategy * newStrategy);

	void init(unsigned newSeed, SelectionStrategy * newStrategy);

	void sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize);

	int getParent(int * populationFitnesses, int populationSize);

	virtual Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize)=0;

	std::string toString();
};
