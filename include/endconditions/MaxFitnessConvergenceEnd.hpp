#include "./FitnessMatchEnd.hpp"
#pragma once

/*
* This ending condition will terminate the GA if more than a given proportion
* of the population has achieved a given fitness
*/

class MaxFitnessConvergenceEnd : public FitnessMatchEnd {
	private:

	protected:
	double populationProportion;

	public:
	MaxFitnessConvergenceEnd(float minimumFitness);
	MaxFitnessConvergenceEnd(
		float minimumFitness,
		double populationProportion
	);

	virtual bool checkCondition(
		vector<Genome*> genomes,
		vector<float> fitnesses,
		unsigned int currentIteration
	);
};
