#include "../core/EndCondition.hpp"
#pragma once

/*
* The fitness matching end condition returns true if an individual in the
* population has a fitness greater than or equal to a specified minimum
* fitness.
*/

class FitnessMatchEnd : public EndCondition {
	private:

	protected:
	int minimumFitness;

	virtual bool checkIndividual(Individual * target);

	public:
	FitnessMatchEnd(int newMinimumFitness);

	virtual bool checkCondition(Individual ** population, int populationSize);
};
