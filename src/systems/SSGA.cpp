#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "systems/SSGA.hpp"

using namespace std;


SSGA::SSGA(SelectionStrategy * newStrategy) : EvolutionarySystem(newStrategy) {
	niching = NULL;
}

SSGA::SSGA(unsigned newSeed, SelectionStrategy * newStrategy) : EvolutionarySystem(newSeed, newStrategy) {
	niching = NULL;
}
SSGA::SSGA(SelectionStrategy * newStrategy, NichingStrategy * newNiching) : EvolutionarySystem(newStrategy) {
	niching = newNiching;
}

SSGA::SSGA(unsigned newSeed, SelectionStrategy * newStrategy, NichingStrategy * newNiching) : EvolutionarySystem(newSeed, newStrategy) {
	niching = newNiching;
}

//This strategy uses the SSGA (Steady State Genetic Algorithm) approach - 1:1
//replacement of parents by offspring, using local elitism
Individual ** SSGA::breedMutateSelect(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
	Individual * firstParent;
	Individual * secondParent;
	Individual ** children;
	Individual ** newPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize);
	int firstFitness;
	int secondFitness;

	int firstIndex;
	int secondIndex;

	for (int i = 0; i < populationSize; i++) {
		newPopulation[i] = NULL;
	}

	firstIndex = getParent(populationFitnesses, populationSize);
	secondIndex = getParent(populationFitnesses, populationSize);

	firstParent = initialPopulation[firstIndex];
	secondParent = initialPopulation[secondIndex];

	children = firstParent->crossoverOperation(secondParent);
	Individual ** finalChildren = (Individual **)malloc(sizeof(Individual*)*2);
	for (int i = 0; i < 2; i++) finalChildren[i] = children[i]->mutationOperation();

	delete(children[0]);
	delete(children[1]);
	free(children);

	int * replacementIndices;
	if (niching != NULL) {
		replacementIndices = niching->getIndices(initialPopulation, populationSize, finalChildren);
	} else {
		replacementIndices = (int*)malloc(sizeof(int)*2);
		replacementIndices[0] = firstIndex;
		replacementIndices[1] = secondIndex;
	}

	//initialPopulation[replacementIndices[0]] = children[0];
	//initialPopulation[replacementIndices[1]] = children[1];
	//free(replacementIndices);

	//delete(children[0]);
	//delete(children[1]);
	//free(children);

	firstFitness = finalChildren[0]->getFitness();
	secondFitness = finalChildren[1]->getFitness();

	if (firstFitness > populationFitnesses[replacementIndices[0]]) {
		//delete(initialPopulation[firstIndex]);

		newPopulation[replacementIndices[0]] = finalChildren[0];
		populationFitnesses[replacementIndices[0]] = firstFitness;
	} else {
		delete(finalChildren[0]);
	}

	if (secondFitness > populationFitnesses[replacementIndices[1]]) {
		//delete(initialPopulation[secondIndex]);

		newPopulation[replacementIndices[1]] = finalChildren[1];
		populationFitnesses[replacementIndices[1]] = secondFitness;
	} else {
		delete(finalChildren[1]);
	}

	free(finalChildren);
	free(replacementIndices);

	for (int i = 0; i < populationSize; i++) {
		if (newPopulation[i] == NULL) {
			newPopulation[i] = initialPopulation[i]->deepCopy();
		}
	}

	return newPopulation;
}
