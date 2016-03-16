#include "Individual.hpp"
#include "SelectionStrategy.hpp"
#include <random>
#include <string>
#pragma once

/*
* By extending this abstract class, we are able to have
* generation-over-generation population replacement handled in a variety of
* different ways - essentially allowing us to build entirely different
* evolutionary systems within the same framework.
*/

class EvolutionarySystem {
	private:

	protected:
	unsigned seed;
	std::mt19937 generator;
	SelectionStrategy * myStrategy;

	Individual ** getEmptyPopulation(int populationSize);

	public:
	EvolutionarySystem(SelectionStrategy * newStrategy);

	EvolutionarySystem(unsigned newSeed, SelectionStrategy * newStrategy);

	void init(unsigned newSeed, SelectionStrategy * newStrategy);

	void sortPopulation(
		Individual ** initialPopulation,
		int * initialFitnesses,
		int populationSize
	);

	virtual int getParent(int * populationFitnesses, int populationSize);

	virtual Individual ** breedMutateSelect(
		Individual ** initialPopulation,
		int * populationFitnesses,
		int populationSize
	)=0;

	std::string toString();
};
