#include <random>
#include "systems/StrongIterativeReplacingGA.hpp"

using namespace std;

StrongIterativeReplacingGA::StrongIterativeReplacingGA(
	SelectionStrategy * newStrategy
) : ReplacingGA(newStrategy) {}

StrongIterativeReplacingGA::StrongIterativeReplacingGA(
	unsigned newSeed,
	SelectionStrategy * newStrategy
) : ReplacingGA(newSeed, newStrategy) {}

Individual ** StrongIterativeReplacingGA::breedMutateSelect(
	Individual ** initialPopulation,
	int populationFitnesses[],
	int populationSize
) {
	Individual ** newPopulation;
	int indexes[2];
	int * newFitnesses;
	int numOffspring = 0;

	Individual * firstParent;
	Individual * secondParent;
	Individual ** children;

	newPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize);

	for (int i = 0; i < populationSize; i++) {
		newPopulation[i] = initialPopulation[i]->deepCopy();
	}

	for (int i = 0; i < populationSize; i++) {
		indexes[0] = i;
		indexes[1] = getParent(populationFitnesses, populationSize);
		firstParent = initialPopulation[indexes[0]];
		secondParent = initialPopulation[indexes[1]];

		children = firstParent->crossoverOperation(secondParent);

		for (int k = 0; k < 2; k++) {
			Individual * tempChild = children[k]->
				mutationOperation();
			delete(children[k]);
			children[k] = tempChild;

			if (children[k]->checkFitness() > newPopulation[indexes[k]]->getFitness()) {
				delete(newPopulation[indexes[k]]);
				newPopulation[indexes[k]] = children[k];
			} else {
				delete(children[k]);
			}
		}

		free(children);
	}

	return(newPopulation);
}
