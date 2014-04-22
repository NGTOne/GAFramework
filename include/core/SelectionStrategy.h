//Separating the selection strategy from the generational model affords us
//significant flexibility in creating different GAs/hierarchical GAs
#include "Individual.h"
#include <random>
#include <string>
#pragma once

class SelectionStrategy {
	private:

	protected:
	unsigned seed;
	std::mt19937 generator;
	int crossoverRate;

	public:

	SelectionStrategy(double newCrossoverRate);
	SelectionStrategy(unsigned newSeed, double newCrossoverRate);

	void init(double newCrossoverRate, unsigned newSeed);

	virtual int getParent(int populationFitnesses[], int populationSize)=0;

	std::string toString();
};
