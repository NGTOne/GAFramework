#include <random>
#include "systems/WeakIterativeReplacingGA.hpp"

using namespace std;

WeakIterativeReplacingGA::WeakIterativeReplacingGA(
	SelectionStrategy * newStrategy
) : ReplacingGA(newStrategy) {}

WeakIterativeReplacingGA::WeakIterativeReplacingGA(
	unsigned newSeed,
	SelectionStrategy * newStrategy
) : ReplacingGA(newSeed, newStrategy) {}

Individual ** WeakIterativeReplacingGA::breedMutateSelect(
	Individual ** initialPopulation,
	int populationFitnesses[],
	int populationSize
) {
	Individual ** newPopulation;
	int indexes[2];
	int * newFitnesses;
	int numOffspring[populationSize];
	Individual * possibleContenders[populationSize][populationSize];

	Individual * firstParent;
	Individual * secondParent;
	Individual ** children;

	newPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize);

	for (int i = 0; i < populationSize; i++) {
		newPopulation[i] = initialPopulation[i]->deepCopy();
		numOffspring[i] = 0;
		for (int k = 0; k < populationSize; k++) {
			possibleContenders[i][k] = NULL;
		}
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
			possibleContenders[indexes[k]][numOffspring[indexes[k]]++] = children[k];
		}

		free(children);
	}

	for (int i = 0; i < populationSize; i++) {
		uniform_int_distribution<int> selDist(0, numOffspring[i]-1);
		int index = selDist(generator);

		if (possibleContenders[i][index]->checkFitness() > newPopulation[i]->getFitness()) {
			delete(newPopulation[i]);
			newPopulation[i] = possibleContenders[i][index]->deepCopy();
		}

		for (int k = 0; k < numOffspring[i]; k++) {
			delete(possibleContenders[i][k]);
		}
	}

	return(newPopulation);
}
