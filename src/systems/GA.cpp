#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "systems/GA.hpp"

using namespace std;

GA::GA(int newNumElites, SelectionStrategy * newStrategy) : EvolutionarySystem(newStrategy) {
	numElites = newNumElites;
}

GA::GA(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy) : EvolutionarySystem(newSeed, newStrategy) {
	numElites = newNumElites;
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
	}

	//Add the elites to the new population
	for (int i = 0; i < numElites; i++) {
		for (int k = 0; k < populationSize; k++) {
			if (populationFitnesses[k] > bestFitness && eliteLocations[k] != true) {
				bestFitness = populationFitnesses[k];
				bestFitnessLocation = k;
			}
		}

		newPopulation[numOffspring] = initialPopulation[bestFitnessLocation]->deepCopy();
		newFitnesses[numOffspring] = bestFitness;
		numOffspring += 1;
		eliteLocations[bestFitnessLocation] = true;
	}

	for(;numOffspring < populationSize;) {
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
	}

	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = newFitnesses[i];
		delete(initialPopulation[i]);
	}

	free(newFitnesses);

	return newPopulation;
}
