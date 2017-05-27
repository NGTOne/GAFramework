#ifndef ENDCONDITIONS_MaxFitnessConvergenceEnd
#define ENDCONDITIONS_MaxFitnessConvergenceEnd

#include "./FitnessMatchEnd.hpp"

/*
* This ending condition will terminate the GA if more than a given proportion
* of the population has achieved a given fitness
*/

class MaxFitnessConvergenceEnd : public FitnessMatchEnd {
	private:

	protected:
	float populationProportion;

	public:
	MaxFitnessConvergenceEnd(double minimumFitness);
	MaxFitnessConvergenceEnd(
		double minimumFitness,
		double populationProportion
	);

	virtual bool checkCondition(
		std::vector<Genome*> genomes,
		std::vector<Fitness> fitnesses,
		unsigned int currentIteration
	);
};

#endif
