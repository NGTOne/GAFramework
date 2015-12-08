#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "generations/ReplacingGAGeneration.hpp"

using namespace std;

ReplacingGAGeneration::ReplacingGAGeneration(SelectionStrategy * newStrategy, double newReplacementRate) : GenerationModel(newStrategy) {
	replacementRate = newReplacementRate;
}

ReplacingGAGeneration::ReplacingGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy, double newReplacementRate) : GenerationModel(newSeed, newStrategy) {
	replacementRate = newReplacementRate;
}

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

	uniform_real_distribution<double> replacementDistribution(0, 1);

	for (int i = 0; i < populationSize/2; i++) {
		for (int k = 0; k < 2; k++) {
			indexes[k] = getParent(populationFitnesses, populationSize);
		}
		firstParent = initialPopulation[indexes[0]];
		secondParent = initialPopulation[indexes[1]];

		children = firstParent->crossoverOperation(secondParent);

		for (int k = 0; k < 2; k++) {
			if (replacementDistribution(generator) < replacementRate) {
				newPopulation[indexes[k]] = children[k]->mutationOperation();
			} else {
				delete(children[k]);
			}
			newPopulation[indexes[k]]->getFitness();
		}

		free(children);
	}

	//free(initialPopulation);
	return(newPopulation);

	/*for(;numOffspring < populationSize;) {
		firstIndex = getParent(populationFitnesses, populationSize);
		secondIndex = getParent(populationFitnesses, populationSize);

		firstParent = initialPopulation[firstIndex];
		secondParent = initialPopulation[secondIndex];

		children = firstParent->crossoverOperation(secondParent);

		firstParent = children[0]->mutationOperation();
		secondParent = children[1]->mutationOperation();

		delete(children[0]);
		delete(children[1]);
		free(children);

		newPopulation[numOffspring] = firstParent;
		newFitnesses[numOffspring++] = firstParent->getFitness();

		if (numOffspring < populationSize) {
			newPopulation[numOffspring] = secondParent;
			newFitnesses[numOffspring++] = secondParent->getFitness();
		}
	}*/

	/*for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = newFitnesses[i];
		delete(initialPopulation[i]);
	}

	free(newFitnesses);

	return newPopulation;*/
}
