#include "endconditions/MaxFitnessConvergenceEnd.hpp"

MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(int newMinimumFitness) : FitnessMatchEnd(newMinimumFitness) {
	populationProportion = 0.5;
}

 MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(int newMinimumFitness, double newPopulationProportion) : FitnessMatchEnd(newMinimumFitness) {
	populationProportion = newPopulationProportion;
}

bool MaxFitnessConvergenceEnd::checkCondition(Individual ** population, int populationSize) {
	double proportion = 0;
	int countMadeIt = 0;
	for (int i = 0; i < populationSize; i++) {
		if (checkIndividual(population[i])) countMadeIt++;
	}

	proportion = (double)countMadeIt/(double)populationSize;

	return proportion >= populationProportion;
}
