#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "generations/ESGeneration.hpp"

using namespace std;

ESGeneration::ESGeneration(int newNumElites, SelectionStrategy * newStrategy) : GenerationModel(newNumElites, newStrategy) {}

ESGeneration::ESGeneration(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy) : GenerationModel(newSeed, newNumElites, newStrategy) {}

//This strategy uses the ES (Evolutionary Strategies) approach - generate all
//the offspring, concatenate them together, sort them by fitness, and then
//truncate to the original population size
Individual ** ESGeneration::breedMutateSelect(Individual ** initialPopulation, int populationFitnesses[], int populationSize) {
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
                newPopulationFitnesses[i+populationSize] = mutantChildren[i]->getFitness();
                overallPopulation[i+(populationSize*2)] = crossoverChildren[i];
                newPopulationFitnesses[i+(populationSize*2)] = crossoverChildren[i]->getFitness();
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
