//This abstract class serves as a general base for all generation models,
//allowing any HierarchicalGenePool to use any model you might want

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "SelectionStrategy.h"
#include "GenerationModel.h"

using namespace std;

GenerationModel::GenerationModel(double newCrossoverRate, int newNumElites, SelectionStrategy * newStrategy) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(newCrossoverRate, newNumElites, seed, newStrategy);
}

GenerationModel::GenerationModel(unsigned newSeed, double newCrossoverRate, int newNumElites, SelectionStrategy * newStrategy) {
	init(newCrossoverRate, newNumElites, newSeed, newStrategy);
}

void GenerationModel::init(double newCrossoverRate, int newNumElites, unsigned newSeed, SelectionStrategy * newStrategy) {
	seed = newSeed;
	numElites = newNumElites;
	crossoverRate = newCrossoverRate;
	mt19937 newGenerator(seed);
	generator = newGenerator;
	myStrategy = newStrategy;
}

void GenerationModel::sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize) {
	//Since we're unlikely to be dealing with gigantic populations, a
	//simple sort that's O(n^2) or better and easy to implement will
	//suffice here.
	//TODO: Make it more efficient
	Individual * tempIndividual;
	int temp;

	for (int i = 0; i < populationSize; i++) {
		for (int k = 0; k < populationSize; k++) {
			if (initialFitnesses[i] > initialFitnesses[k]) {
				tempIndividual = initialPopulation[i];
				temp = initialFitnesses[i];

				initialPopulation[i] = initialPopulation[k];
				initialFitnesses[i] = initialFitnesses[k];

				initialPopulation[k] = tempIndividual;
				initialFitnesses[k] = temp;
			}
		}
	}
}

//This strategy uses the SSGA (Steady State Genetic Algorithm) approach - 1:1
//replacement of parents by offspring, using local elitism
Individual ** SelectionStrategy::SSGAReplace(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
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
			populationFitnesses[i] = initialPopulation[i]->checkFitness();
		}
		delete(initialPopulation[i]);
	}

	return newPopulation;
}

//This strategy uses the GA (Genetic Algorithms) approach - pick a few elites,
//then fill the rest of the population in with new individuals
Individual ** SelectionStrategy::GAReplace(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
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
	int bestFitnessLocation;

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
		newFitnesses[numOffspring++] = firstParent->checkFitness();

		if (numOffspring < populationSize) {
			newPopulation[numOffspring] = secondParent;
			newFitnesses[numOffspring++] = secondParent->checkFitness();
		}
	}

	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = newFitnesses[i];
		delete(initialPopulation[i]);
	}

	free(newFitnesses);

	return newPopulation;
}

//This strategy uses the ES (Evolutionary Strategies) approach - generate all
//the offspring, concatenate them together, sort them by fitness, and then
//truncate to the original population size
Individual ** SelectionStrategy::ESReplace(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
        Individual ** mutantChildren;
        Individual ** crossoverChildren;
        Individual ** finalPopulation;
        Individual ** overallPopulation;
        int newPopulationFitnesses[populationSize*3];
        int finalPopulationFitnesses[populationSize];

        Individual * firstParent;
        Individual * secondParent;
        Individual ** children;

        int firstIndex;
        int secondIndex;

        crossoverChildren = (Individual**)malloc(sizeof(Individual*)*populationSize);
	mutantChildren = (Individual**)malloc(sizeof(Individual*)*populationSize);
        finalPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize);
        overallPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize*3);

        for (int i = 0; i < populationSize; i++) {
                finalPopulationFitnesses[i] = 0;
        }

        for (int i = 0; i < populationSize*3; i++) {
                newPopulationFitnesses[i] = 0;
        }

        //Each individual produces one mutant
        for (int i = 0; i < populationSize; i++) {
                mutantChildren[i] = initialPopulation[i]->mutationOperation();
        }

	//Make n/2 crossover attempts
        for (int i = 0; i < (populationSize/2)*2; i+=2) {
                firstIndex = getParent(populationFitnesses, populationSize);
                secondIndex = getParent(populationFitnesses, populationSize);
                firstParent = initialPopulation[firstIndex];
                secondParent = initialPopulation[secondIndex];

                children = firstParent->crossoverOperation(secondParent);

                crossoverChildren[i] = children[0];
                crossoverChildren[i+1] = children[1];

                free(children);
        }

        //OK, now we have all the results of our breeding and mutation
        //Time to pick the ones that will move on to the next generation
        //First, we lump them all together into one big population
        for (int i = 0; i < populationSize; i++) {
                overallPopulation[i] = initialPopulation[i];
                newPopulationFitnesses[i] = populationFitnesses[i];
                overallPopulation[i+populationSize] = mutantChildren[i];
                newPopulationFitnesses[i+populationSize] = mutantChildren[i]->checkFitness();
                overallPopulation[i+(populationSize*2)] = crossoverChildren[i];
                newPopulationFitnesses[i+(populationSize*2)] = crossoverChildren[i]->checkFitness();
        }

        //Now, of course, we sort them
        sortPopulation(overallPopulation, newPopulationFitnesses, populationSize*3);

        //Since they're sorted, the best of the new generation can simply be
        //pulled from the top of the list
        for (int i = 0; i < populationSize; i++) {
                finalPopulation[i] = overallPopulation[i]->deepCopy();
                finalPopulationFitnesses[i] = newPopulationFitnesses[i];
        }

	for (int i = 0; i < populationSize*3; i++) {
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

//TODO: Implement other replacement strategies
Individual ** SelectionStrategy::breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize) {
	int * newFitnesses = (int*)malloc(sizeof(int)*populationSize);
	Individual ** newPopulation = NULL;

	for (int i = 0; i < populationSize; i++) {
		newFitnesses[i] = populationFitnesses[i];
	}

	if (replaceMode == 's') {
		newPopulation = SSGAReplace(initialPopulation, newFitnesses, populationSize);
	} else if (replaceMode == 'e') {
		newPopulation = ESReplace(initialPopulation, newFitnesses, populationSize);
	} else if (replaceMode == 'g') {
		newPopulation = GAReplace(initialPopulation, newFitnesses, populationSize);
	}

	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = newFitnesses[i];
	}

	free(newFitnesses);
	
	return newPopulation;
}

string SelectionStrategy::toString() {
	string returnString = "";
        stringstream ss;
	
	ss << "Random seed: " << seed << "\nCrossover rate: " << crossoverRate << "\nNumber of elites: " << numElites << "\nSelection Strategy: ";

	ss << myStrategy->toString();

	ss << "\n";

	returnString = ss.str();

	return returnString;
}
