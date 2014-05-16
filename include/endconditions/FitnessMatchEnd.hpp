#include "../core/EndCondition.hpp"
#pragma once

class FitnessMatchEnd : public EndCondition {
	private:

	protected:
	
	int minimumFitness;

	public:
	FitnessMatchEnd(int newMinimumFitness);

	virtual bool checkCondition(Individual * individualToCheck);
};
