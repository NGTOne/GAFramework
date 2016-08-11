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
	float minimumFitness;

	virtual bool checkSolution(Genome* target, float targetFitness);

	public:
	FitnessMatchEnd(float minimumFitness);

	virtual bool checkCondition(
		std::vector<Genome*> genomes,
		std::vector<float> fitnesses,
		unsigned int currentIteration
	);
};
