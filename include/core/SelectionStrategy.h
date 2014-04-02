//This abstract class serves as a general base for all selection strategies,
//allowing any HierarchicalGenePool to use any strategy you might want
#include "Individual.h"
#include <random>
#include <string>
#pragma once

class SelectionStrategy {
	private:

	protected:
	unsigned seed;
	double crossoverRate;
	int numElites;
	std::mt19937 generator;
	char replaceMode;

	public:

	SelectionStrategy();
	SelectionStrategy(double newCrossoverRate, int newNumElites, char newReplaceMode);

	SelectionStrategy(unsigned newSeed, double newCrossoverRate, int newNumElites, char newReplaceMode);

	void init(double newCrossoverRate, int newNumElites, unsigned newSeed, char newReplaceMode);

	void sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize);

	virtual int getParent(int populationFitnesses[], int populationSize)=0;

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);

	Individual ** SSGAReplace(Individual ** initialPopulation, int * populationFitnesses, int populationSize);

	Individual ** GAReplace(Individual ** initialPopulation, int * populationFitnesses, int populationSize);

	Individual ** ESReplace(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
	std::string toString();
};
