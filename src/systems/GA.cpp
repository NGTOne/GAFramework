#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "systems/GA.hpp"

using namespace std;

GA::GA(
	int numElites,
	bool randomElitePlacement,
	SelectionStrategy * strategy
) : EvolutionarySystem(strategy) {
	init(numElites, randomElitePlacement);
}

GA::GA(
	int numElites,
	SelectionStrategy * strategy
) : EvolutionarySystem(strategy) {
	init(numElites, false);
}

GA::GA(
	unsigned seed,
	int numElites,
	bool randomElitePlacement,
	SelectionStrategy * strategy
) : EvolutionarySystem(seed, strategy) {
	init(numElites, randomElitePlacement);
}

void GA::init(int numElites, bool randomElitePlacement) {
	this->numElites = numElites;
	this->randomElitePlacement = randomElitePlacement;
}

int GA::getEliteIndex(Individual ** newPopulation, int populationSize) {
	if (!randomElitePlacement) {
		for (int i = 0; i < populationSize; i++) {
			if (newPopulation[i] == NULL) return i;
		}
	} else {
		uniform_int_distribution<int> dist(0, populationSize-1);
		int index = dist(generator);

		while (newPopulation[index] != NULL) {
			index = dist(generator);
		}

		return index;
	}
}

//This strategy uses the GA (Genetic Algorithms) approach - pick a few elites,
//then fill the rest of the population in with new individuals
Individual ** GA::breedMutateSelect(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
	if (numElites >= populationSize) int numElites = populationSize/2;
	Individual ** newPopulation;
	int * newFitnesses;
	bool eliteLocations[populationSize];
	int numOffspring = 0;

	int firstIndex;
	int secondIndex;
	Individual * firstParent;
	Individual * secondParent;
	Individual ** children;

	int bestFitness = 0;
	int bestFitnessLocation = 0;

	newPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize);
	newFitnesses = (int*)malloc(sizeof(int)*populationSize);

	for (int i = 0; i < populationSize; i++) {
		eliteLocations[i] = false;
		newPopulation[i] = NULL;
	}

	//Add the elites to the new population
	for (int i = 0; i < numElites; i++) {
		for (int k = 0; k < populationSize; k++) {
			if (populationFitnesses[k] > bestFitness && eliteLocations[k] != true) {
				bestFitness = populationFitnesses[k];
				bestFitnessLocation = k;
			}
		}

		int index = getEliteIndex(newPopulation, populationSize);
		newPopulation[index] = initialPopulation[bestFitnessLocation]->deepCopy();
		newFitnesses[index] = bestFitness;
		eliteLocations[bestFitnessLocation] = true;
	}

	while(numOffspring < populationSize) {
		firstIndex = getParent(populationFitnesses, populationSize);
		secondIndex = getParent(populationFitnesses, populationSize);

		firstParent = initialPopulation[firstIndex];
		secondParent = initialPopulation[secondIndex];

		children = firstParent->crossoverOperation(secondParent);

		firstParent = children[0]->mutationOperation();
		secondParent = children[1]->mutationOperation();

		while (newPopulation[numOffspring++] != NULL);

		delete(children[0]);
		delete(children[1]);
		free(children);

		newPopulation[numOffspring] = firstParent;
		newFitnesses[numOffspring++] = firstParent->getFitness();

		if (numOffspring < populationSize) {
			newPopulation[numOffspring] = secondParent;
			newFitnesses[numOffspring++] = secondParent->getFitness();
		}
	}

	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = newFitnesses[i];
	}

	free(newFitnesses);

	return newPopulation;
}
