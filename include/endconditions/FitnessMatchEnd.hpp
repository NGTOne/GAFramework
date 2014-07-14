#include "../core/EndCondition.hpp"
#pragma once

//This end condition verifies whether or not the MAXIMUM fitness of the
//population is greater than or equal to the specified fitness, and ends
//the GA if it is.
class FitnessMatchEnd : public EndCondition {
	private:

	protected:
	
	int minimumFitness;

	public:
	FitnessMatchEnd(int newMinimumFitness);

	virtual bool checkCondition(Individual * individualToCheck);
};
