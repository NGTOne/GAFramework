#include <propagators/apportioning/WeightedAveragePropagator.hpp>

int WeightedAveragePropagator::getAssignableFitness(Individual ** population, int populationSize, Individual * target) {
	int i, *uses, weightedContribution=0;

	uses = this->getUseCount(population, populationSize, target);

	for (i = 0; i < populationSize; i++) {
		weightedContribution += this->getFitnessValue(population[i], target) * uses[i];
	}

	free(uses);

	return weightedContribution/this->getIndividualCount(population, populationSize, target);
}
