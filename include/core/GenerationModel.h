//This abstract class serves as a general base for all generational models,
//allowing any HierarchicalGenePool to use any model you might want
#include "Individual.h"
#include "SelectionStrategy.h"
#include <random>
#include <string>
#pragma once

class GenerationModel {
	private:

	protected:
	unsigned seed;
	int numElites;
	std::mt19937 generator;
	SelectionStrategy * myStrategy;

	public:

	GenerationModel(int newNumElites, SelectionStrategy * newStrategy);

	GenerationModel(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy);

	void init(int newNumElites, unsigned newSeed, SelectionStrategy * newStrategy);

	void sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize);

	int getParent(int * populationFitnesses, int populationSize);

	virtual Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize)=0;

	std::string toString();
};
