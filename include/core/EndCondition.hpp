#include "Genome.hpp"
#include <vector>
#pragma once

class EndCondition {
	private:

	protected:
	virtual bool checkSolution(Genome * target, float targetFitness);
	
	public:
	EndCondition();
	virtual ~EndCondition();

	virtual bool checkCondition(
		std::vector<Genome*> genomes,
		std::vector<float> fitnesses,
		unsigned int currentIteration
	)=0;
};
