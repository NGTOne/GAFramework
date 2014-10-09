#include "Individual.hpp"
#include <random>
#include <string>
#pragma once

/*
* The SelectionStrategy abstract class allows selection for breeding to occur
* in a variety of different ways, so that various different strategies can
* simply by "plugged into" a genetic algorithm to observe the results. By
* separating it from the generation model, we can create a wide variety of
* different combinations, with varying effects. This class also allows us to
* use various different selection strategies (as appropriate) at different
* levels of a hierarchical GA.
*/

class SelectionStrategy {
	private:

	protected:
	unsigned seed;
	std::mt19937 generator;
	double crossoverRate;
	std::string name;

	SelectionStrategy(unsigned newSeed, double newCrossoverRate, std::string newName);

	public:

	SelectionStrategy(double newCrossoverRate);
	SelectionStrategy(unsigned newSeed, double newCrossoverRate);

	void init(double newCrossoverRate, unsigned newSeed, std::string newName);

	virtual int getParent(int populationFitnesses[], int populationSize)=0;

	std::string toString();
};
