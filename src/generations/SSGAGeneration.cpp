#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "generations/SSGAGeneration.hpp"

using namespace std;

SSGAGeneration::SSGAGeneration(SelectionStrategy * newStrategy, NichingStrategy newNiching) : GenerationModel(newStrategy) {
		niching = newNiching;
	}

SSGAGeneration::SSGAGeneration(unsigned newSeed, SelectionStrategy * newStrategy, NichingStrategy newStrategy) : GenerationModel(newSeed, newStrategy) {
		niching = newNiching;
	}

//This strategy uses the SSGA (Steady State Genetic Algorithm) approach - 1:1
//replacement of parents by offspring, using local elitism
Individual ** SSGAGeneration::breedMutateSelect(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
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

	//delete(firstParent);
	//delete(secondParent);

	children[0] = children[0]->mutationOperation();
	children[1] = children[1]->mutationOperation();

	int replacementIndices[];
	replacementIndices = (niching != null ? niching->getIndices(initialPopulation) : {firstIndex, secondIndex});

	initialPopulation[replacementIndices[0]] = children[0];
	initialPopulation[replacementIndices[1]] = children[1];

	delete(children[0]);
	delete(children[1]);
	free(children);

	firstFitness = firstParent->getFitness();
	secondFitness = secondParent->getFitness();

	if (firstFitness > populationFitnesses[firstIndex]) {
		//delete(initialPopulation[firstIndex]);

		newPopulation[firstIndex] = firstParent;
		populationFitnesses[firstIndex] = firstFitness;
	} else {
		delete(firstParent);
	}

	if (secondFitness > populationFitnesses[secondIndex]) {
		//delete(initialPopulation[secondIndex]);

		newPopulation[secondIndex] = secondParent;
		populationFitnesses[secondIndex] = secondFitness;
	} else {
		delete(secondParent);
	}

	for (int i = 0; i < populationSize; i++) {
		if (newPopulation[i] == NULL) {
			newPopulation[i] = initialPopulation[i]->deepCopy();
		}
		delete(initialPopulation[i]);
	}

	return newPopulation;
}
