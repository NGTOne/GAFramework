#include "Individual.hpp"
#pragma once

//The EndCondition class provides a simple way to provide an "evaluative"
//ending condition for GAs - this allows the GA to end before the maximum
//number of generations have elapsed, when some goalpost has been reached.
class EndCondition {
	private:

	protected:
	
	public:
	EndCondition();

	~EndCondition();

	virtual bool checkCondition(Individual * individualToCheck);
};
