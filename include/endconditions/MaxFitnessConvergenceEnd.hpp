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
	MaxFitnessConvergenceEnd(int newMinimumFitness);
	MaxFitnessConvergenceEnd(
		int newMinimumFitness,
		double newPopulationProportion
	);

	virtual bool checkCondition(
		Individual ** population,
		int populationSize
	);
};
