#include "Individual.hpp"
#pragma once

/*
* This abstract class allows us to specify an ending condition for the
* genetic algorithm other than having a number of generations go by.
* This can be something like having an individual in the population reach
* a given fitness, or the population as a whole reaching some milestone.
*/

class EndCondition {
	private:

	protected:
	
	public:
	EndCondition();

	~EndCondition();

	virtual bool checkCondition(Individual * individualToCheck);
};
