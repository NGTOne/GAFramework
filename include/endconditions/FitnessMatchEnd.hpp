#include "../core/EndCondition.hpp"
#pragma once

/*
* The fitness matching end condition returns true if any individual in the
* population has a fitness greater than or equal to a specified minimum
* fitness.
*/

class FitnessMatchEnd : public EndCondition {
	private:

	protected:
	int minimumFitness;

	virtual bool checkSolution(Genome * target, int targetFitness);

	public:
	FitnessMatchEnd(int minimumFitness);

	virtual bool checkCondition(
		vector<Genome*> genomes,
		vector<int> fitnesses,
		int currentIteration
	);
};
