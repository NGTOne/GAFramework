#include <propagators/apportioning/SummingPropagator.hpp>

int SummingPropagator::getAssignableFitness(Individual ** population, int populationSize, Individual * target) {
	int i, totalContribution=0;

	for (i = 0; i < populationSize; i++) {
		totalContribution += this->getFitnessValue(population[i], target);
	}

	return totalContribution;
}
