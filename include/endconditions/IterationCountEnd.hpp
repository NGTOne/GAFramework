#include "../core/EndCondition.hpp"
#pragma once

/*
* This end condition will return true if the number of elapsed iterations of
* the algorithm reaches the specified threshold
*/

class IterationCountEnd : public EndCondition {
	private:

	protected:
	unsigned int maxIterations;

	public:
	IterationCountEnd(unsigned int maxIterations);

	virtual bool checkCondition(
		vector<Genome*> genomes,
		vector<int> fitnesses,
		int currentIteration
	);
};
