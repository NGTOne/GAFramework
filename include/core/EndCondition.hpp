#include "Genome.hpp"
#include <vector>
#pragma once

class EndCondition {
	private:

	protected:
	virtual bool checkSolution(Genome * target, int targetFitness);
	
	public:
	EndCondition();
	virtual ~EndCondition();

	virtual bool checkCondition(
		std::vector<Genome*> genomes,
		std::vector<int> fitnesses,
		unsigned int currentIteration
	)=0;
};
