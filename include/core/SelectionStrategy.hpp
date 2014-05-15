//Separating the selection strategy from the generational model affords us
//significant flexibility in creating different GAs/hierarchical GAs
#include "Individual.hpp"
#include <random>
#include <string>
#pragma once

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
