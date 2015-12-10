#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "generations/ReplacingGAGeneration.hpp"

using namespace std;

ReplacingGAGeneration::ReplacingGAGeneration(SelectionStrategy * newStrategy) : GenerationModel(newStrategy) {}

ReplacingGAGeneration::ReplacingGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy) : GenerationModel(newSeed, newStrategy) {}

bool ReplacingGAGeneration::inPopulation(Individual * target, Individual ** population, int populationSize) {
	for (int i = 0; i < populationSize; i++) {
		if (population[i] == target) return true;
	}

	return false;
}

void ReplacingGAGeneration::removeUnusedIndividuals(Individual ** initialPopulation, Individual ** newPopulation, int populationSize) {
	Individual * temp;

	for (int i = 0; i < populationSize; i++) {
		if (!inPopulation(initialPopulation[i], newPopulation, populationSize)) delete(initialPopulation[i]);
	}
}

Individual ** ReplacingGAGeneration::breedMutateSelect(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
	Individual ** newPopulation;
	int indexes[2];
	int * newFitnesses;
	int numOffspring = 0;

	Individual * firstParent;
	Individual * secondParent;
	Individual ** children;

	newPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize);

	for (int i = 0; i < populationSize; i++) newPopulation[i] = initialPopulation[i];

	for (int i = 0; i < populationSize/2; i++) {
		for (int k = 0; k < 2; k++) {
			indexes[k] = getParent(populationFitnesses, populationSize);
		}
		firstParent = initialPopulation[indexes[0]];
		secondParent = initialPopulation[indexes[1]];

		children = firstParent->crossoverOperation(secondParent);

		for (int k = 0; k < 2; k++) {
			children[k] = children[k]->mutationOperation();

			if (children[k]->checkFitness() > newPopulation[indexes[k]]->getFitness()) {
				newPopulation[indexes[k]] = children[k];
			}
		}

		free(children);
	}

	return(newPopulation);
}
