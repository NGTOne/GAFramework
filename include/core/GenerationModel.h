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
	double crossoverRate;
	int numElites;
	std::mt19937 generator;
	char replaceMode;
	SelectionStrategy * myStrategy;

	public:

	GenerationModel(double newCrossoverRate, int newNumElites, SelectionStrategy * newStrategy);

	GenerationModel(unsigned newSeed, double newCrossoverRate, int newNumElites, SelectionStrategy * newStrategy);

	void init(double newCrossoverRate, int newNumElites, unsigned newSeed, SelectionStrategy * newStrategy);

	void sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize);

	int getParent(int * populationFitnesses, int populationSize);

	virtual Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize)=0;

	std::string toString();
};
