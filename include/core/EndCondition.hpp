#include "Individual.hpp"
#pragma once

class EndCondition {
	private:

	protected:
	
	public:
	EndCondition();

	~EndCondition();

	virtual bool checkCondition(Individual * individualToCheck);
};
