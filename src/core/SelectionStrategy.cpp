//This abstract class serves as a general base for all selection strategies,
//allowing any HierarchicalGenePool to use any strategy you might want

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "SelectionStrategy.h"

using namespace std;

//EMPTY CONSTRUCTOR - DO NOT USE EVER
SelectionStrategy::SelectionStrategy() {};

SelectionStrategy::SelectionStrategy(double newCrossoverRate, int newNumElites, char newReplaceMode) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(newCrossoverRate, newNumElites, seed, newReplaceMode);
}

SelectionStrategy::SelectionStrategy(unsigned newSeed, double newCrossoverRate, int newNumElites, char newReplaceMode)  {
	init(newCrossoverRate, newNumElites, newSeed, newReplaceMode);
}

void SelectionStrategy::init(double newCrossoverRate, int newNumElites, unsigned newSeed, char newReplaceMode) {
	seed = newSeed;
	numElites = newNumElites;
	crossoverRate = newCrossoverRate;
	mt19937 newGenerator(seed);
	generator = newGenerator;
	replaceMode = newReplaceMode;
}

void SelectionStrategy::sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize) {
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

//TODO: Make a separate class for replacement strategies
//It's ugly, but good enough for now

//This strategy uses the GA (Genetic Algorithm) approach - 1:1 replacement of
//parents by offspring, with some elites that don't change
Individual ** SelectionStrategy::GAReplace(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
	Individual * firstParent;
	Individual * secondParent;
	Individual ** children;
	int eliteLocations[populationSize];
	Individual ** newPopulation;

	int firstIndex;
	int secondIndex;

	int bestFitness = 0;
	int bestFitnessIndex;

	newPopulation = (Individual**)malloc(sizeof(Individual*)*populationSize);

	for (int i = 0; i < populationSize; i++) {
		eliteLocations[i] = 0;
		newPopulation[i] = NULL;
	}

	//Deciding which ones are elite
	for (int i = 0; i < numElites; i++) {
		bestFitness = 0;
		for (int k = 0; k < populationSize; k++) {
			if (populationFitnesses[k] > bestFitness && eliteLocations[k] == 0) {
				bestFitness = populationFitnesses[k];
				bestFitnessIndex = k;
			}
		}
		eliteLocations[bestFitnessIndex] = 1;
	}

	//Doing the crossovers - we try for crossover n/2 times
	for (int i = 0; i < populationSize/2; i++) {
		firstIndex = getParent(populationFitnesses, populationSize);
		secondIndex = getParent(populationFitnesses, populationSize);

		firstParent = initialPopulation[firstIndex];
		secondParent = initialPopulation[secondIndex];

		children = firstParent->crossoverOperation(secondParent);

		firstParent = children[0]->mutationOperation();
		secondParent = children[1]->mutationOperation();

		if (eliteLocations[firstIndex] == 0 && firstParent->checkFitness() > populationFitnesses[firstIndex]) {
			newPopulation[firstIndex] = firstParent;
			populationFitnesses[firstIndex] = firstParent->checkFitness();
		}

		if (eliteLocations[secondIndex] == 0 && secondParent->checkFitness() > populationFitnesses[secondIndex]) {
			newPopulation[secondIndex] = secondParent;
			populationFitnesses[secondIndex] = secondParent->checkFitness();
		}
		//newPopulation[firstIndex] = children[0];
		//newPopulation[secondIndex] = children[1];

		//delete(firstParent);
		//delete(secondParent);
		free(children);
	}

	//Each individual, new or old, mutates itself
	for (int i = 0; i < populationSize; i++) {
		if (eliteLocations[i] == 0) {
			
			firstParent = initialPopulation[i]->mutationOperation();
			
			int mutantFitness = firstParent->checkFitness();

			if (mutantFitness > populationFitnesses[i]) {
				newPopulation[i] = firstParent;
				populationFitnesses[i] = mutantFitness;
			}
			//delete(firstParent);
		}

		if (newPopulation[i] == NULL) {
			newPopulation[i] = initialPopulation[i];
			populationFitnesses[i] = initialPopulation[i]->checkFitness();
		}
	}

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
Individual ** SelectionStrategy::breedMutateSelect(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
	if (replaceMode == 'g') {
		return GAReplace(initialPopulation, populationFitnesses, populationSize);
	} else if (replaceMode == 'e') {
		return ESReplace(initialPopulation, populationFitnesses, populationSize);
	}

	//Should not happen EVER - something has gone VERY wrong somewhere if
	//it does
	return NULL;
}

string SelectionStrategy::toString() {
	string returnString = "";
        stringstream ss;
	
	ss << "Random seed: " << seed << "\nCrossover rate: " << crossoverRate << "\nNumber of elites: " << numElites << "\nReplacement mode: ";

	if (replaceMode == 'g') {
		ss << "GA";
	} else if (replaceMode == 'e') {
		ss << "ES";
	}

	ss << "\n";

	returnString = ss.str();

	return returnString;
}
