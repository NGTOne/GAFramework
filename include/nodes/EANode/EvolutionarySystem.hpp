#include "../../core/Solution.hpp"
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
	SelectionStrategy * strategy;

	void init(unsigned newSeed, SelectionStrategy * newStrategy);

	public:
	EvolutionarySystem(SelectionStrategy * newStrategy);
	EvolutionarySystem(unsigned newSeed, SelectionStrategy * newStrategy);

	void sortPopulation(std::vector<Solution *> population);
	virtual int getParent(std::vector<Solution*> population);
	virtual std::vector<Solution*> breedMutateSelect(
		std::vector<Solution*> population
	)=0;

	std::string toString();
};
