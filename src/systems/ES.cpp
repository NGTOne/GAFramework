#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "systems/ES.hpp"

using namespace std;

ES::ES() : EvolutionarySystem(NULL) {
	init(1, 1);
}

ES::ES(unsigned seed) : EvolutionarySystem(seed, NULL) {
	init(1, 1);
}

ES::ES(SelectionStrategy * strategy) : EvolutionarySystem(strategy) {
	init(1, 1);
}

ES::ES(
	unsigned seed,
	SelectionStrategy * strategy
) : EvolutionarySystem(seed, strategy) {
	init(1, 1);
}

ES::ES(double muRatio, double rhoRatio) : EvolutionarySystem(NULL) {
	init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	unsigned seed
) : EvolutionarySystem(seed, NULL) {
	init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	SelectionStrategy * newStrategy
) : EvolutionarySystem(newStrategy) {
	init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	unsigned newSeed,
	SelectionStrategy * newStrategy
) : EvolutionarySystem(newSeed, newStrategy) {
	init(muRatio, rhoRatio);
}

void ES::init(double muRatio, double rhoRatio) {
	this->muRatio = muRatio;
	this->rhoRatio = rhoRatio;
}

int ES::getRandomParent(int populationSize) {
	uniform_int_distribution<int> selectionDist(0, populationSize-1);
	return selectionDist(generator);
}

int ES::getParent(int * populationFitnesses, int populationSize) {
	if (myStrategy == NULL) {
		return getRandomParent(populationSize);
	} else {
		return EvolutionarySystem::getParent(
			populationFitnesses,
			populationSize
		);
	}
}

//This strategy uses the ES (Evolutionary Strategies) approach - generate all
//the offspring, concatenate them together, sort them by fitness, and then
//truncate to the original population size
Individual ** ES::breedMutateSelect(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
	Individual ** mutantChildren;
	Individual ** crossoverChildren;
	Individual ** finalPopulation;
	Individual ** overallPopulation;
	int numCrossChildren = (double)populationSize*muRatio;
	int numMutants = (double)populationSize*rhoRatio;
	int overallPopSize = populationSize + numCrossChildren + numMutants;

	int newPopulationFitnesses[overallPopSize];
	int finalPopulationFitnesses[populationSize];

	Individual * firstParent;
	Individual * secondParent;
	Individual ** children;

	int firstIndex;
	int secondIndex;

	crossoverChildren = (Individual**)malloc(
		sizeof(Individual*)*numCrossChildren);
	mutantChildren = (Individual**)malloc(
		sizeof(Individual*)*numMutants);
	finalPopulation = (Individual**)malloc(
		sizeof(Individual*)*populationSize);
	overallPopulation = (Individual**)malloc(
		sizeof(Individual*)*overallPopSize);

	for (int i = 0; i < populationSize; i++) {
		finalPopulationFitnesses[i] = 0;
	}

	for (int i = 0; i < overallPopSize; i++) {
		newPopulationFitnesses[i] = 0;
	}

	// We produce rho mutants
	for (int i = 0; i < numMutants; i++) {
		firstIndex = getRandomParent(populationSize);
		mutantChildren[i] = initialPopulation[firstIndex]
			->mutationOperation();
	}

	//Make mu crossover attempts
	for (int i = 0; i < numCrossChildren; i++) {
		firstIndex = getParent(populationFitnesses, populationSize);
		secondIndex = getParent(populationFitnesses, populationSize);
		firstParent = initialPopulation[firstIndex];
		secondParent = initialPopulation[secondIndex];

		children = firstParent->crossoverOperation(secondParent);

		// Pick one of the children at random and toss the other away
		firstIndex = getRandomParent(2);
		secondIndex = 1-firstIndex;
		crossoverChildren[i] = children[firstIndex];
		delete(children[secondIndex]);

		free(children);
	}

	//OK, now we have all the results of our breeding and mutation
	//Time to pick the ones that will move on to the next generation
	//First, we lump them all together into one big population
	for (int i = 0; i < populationSize; i++) {
		overallPopulation[i] = initialPopulation[i]->deepCopy();
		newPopulationFitnesses[i] = populationFitnesses[i];
	}

	for (int i = 0; i < numMutants; i++) {
		overallPopulation[i + populationSize] = mutantChildren[i];
		newPopulationFitnesses[i + populationSize] = mutantChildren[i]
			->getFitness();
	}

	for (int i = 0; i < numCrossChildren; i++) {
		overallPopulation[i + populationSize + numMutants]
			= crossoverChildren[i];
		newPopulationFitnesses[i + populationSize + numMutants]
			= crossoverChildren[i]->getFitness();
	}

	//Now, of course, we sort them
	sortPopulation(
		overallPopulation,
		newPopulationFitnesses,
		overallPopSize
	);

	//Since they're sorted, the best of the new generation can simply be
	//pulled from the top of the list
	for (int i = 0; i < populationSize; i++) {
		finalPopulation[i] = overallPopulation[i]->deepCopy();
		finalPopulationFitnesses[i] = newPopulationFitnesses[i];
	}

	// A little housekeeping
	for (int i = 0; i < overallPopSize; i++) {
		delete(overallPopulation[i]);
	}

	free(mutantChildren);
	free(crossoverChildren);
	free(overallPopulation);

	//Return the new population and fitness values
	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = finalPopulationFitnesses[i];
	}
	return finalPopulation;
}
