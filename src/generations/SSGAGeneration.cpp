#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "SSGAGeneration.h"

using namespace std;

SSGAGeneration::SSGAGeneration(int newNumElites, SelectionStrategy * newStrategy) : GenerationModel(newNumElites, newStrategy) {}

SSGAGeneration::SSGAGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy) : GenerationModel(newSeed, newNumElites, newStrategy) {}

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

	firstParent = children[0]->mutationOperation();
	secondParent = children[1]->mutationOperation();

	delete(children[0]);
	delete(children[1]);
	free(children);

	firstFitness = firstParent->checkFitness();
	secondFitness = secondParent->checkFitness();

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
