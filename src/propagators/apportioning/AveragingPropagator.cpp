#include <propagators/apportioning/AveragingPropagator.hpp>

int AveragingPropagator::getAssignableFitness(Individual ** population, int populationSize, Individual * target) {
	int i, useCount, totalContribution=0;

	useCount = this->getIndividualCount(population, populationSize, target);

	for (i = 0; i < populationSize; i++) {
		totalContribution += this->getFitnessValue(population[i], target);
	}

	return totalContribution/useCount;
}
