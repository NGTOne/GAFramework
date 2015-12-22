#include "systems/niching/Crowding.hpp"

int * Crowding::getIndices(Individual ** initialPopulation, int populationSize, Individual ** newIndividuals) {
	int * indices = (int*)malloc(sizeof(int)*2);
	int i, k, c, highestValue, highestIndex;;
	int differences[populationSize];

	for (i = 0; i < 2; i++) {
		highestValue = highestIndex = 0;
		Genome * genome = newIndividuals[i]->getGenome();

		for (k = 0; k < populationSize; k++) {
			differences[k] = genome->getDifference(initialPopulation[k]->getGenome());
			if (differences[k] > highestValue) {
				int alreadyUsed = 0;
				for (c = 0; c < i; c++) {
					if (indices[c] == k) alreadyUsed = 1;
				}
				if (!alreadyUsed) {
					highestValue = differences[k];
					highestIndex = k;
				}
			}
		}

		indices[i] = highestIndex;

		return indices;
	}
}
