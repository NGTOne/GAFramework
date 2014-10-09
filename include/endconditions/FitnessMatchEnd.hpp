#include "../core/EndCondition.hpp"
#pragma once

/*
* The fitness matching end condition returns true if the individual presented
* to it has a fitness greater than or equal to a specified minimum fitness.
*/

class FitnessMatchEnd : public EndCondition {
	private:

	protected:
	
	int minimumFitness;

	public:
	FitnessMatchEnd(int newMinimumFitness);

	virtual bool checkCondition(Individual * individualToCheck);
};
