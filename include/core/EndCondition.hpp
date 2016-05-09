#include "Genome.hpp"
#include <vector>
#pragma once

class EndCondition {
	private:

	protected:
	virtual bool checkSolution(Genome * target);
	
	public:
	EndCondition();
	~EndCondition();

	virtual bool checkCondition(
		std::vector<Genome*> genomes,
		std::vector<int> fitnesses,
		int currentIteration
	)=0;
};
