#include "Solution.hpp"
#include "PopulationNode.hpp"
#include <vector>
#pragma once

class EndCondition {
	private:

	protected:
	virtual bool checkSolution(Solution * target)=0;
	
	public:
	EndCondition();
	~EndCondition();

	virtual bool checkCondition(PopulationNode * node)=0;
};
