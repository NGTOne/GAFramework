#include "Genome.hpp"
#include "PopulationNode.hpp"
#include <vector>
#pragma once

class EndCondition {
	private:

	protected:
	virtual bool checkSolution(Genome * target)=0;
	
	public:
	EndCondition();
	~EndCondition();

	virtual bool checkCondition(PopulationNode * node)=0;
};
