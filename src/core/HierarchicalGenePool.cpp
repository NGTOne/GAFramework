//This is a dual-purpose class for gene pools - it serves as a "base"
//GA, and also as a gene pool for individuals in hierarchical GAs
//Since these functions are, by and large, very similar, they can be
//combined together into one class

#include "core/HierarchicalGenePool.hpp"
#include <sstream>
#include <iostream>

using namespace std;

//If we don't know the optimum
HierarchicalGenePool::HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, GenerationModel * newModel, EndCondition * newCondition) : GenePool() {
	init(newPopulationSize, templateIndividual, myMaxGenerations, numIterations, newModel, newCondition);
}

//Unknown optimum, overridden seed
HierarchicalGenePool::HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, int newSeed, GenerationModel * newModel, EndCondition * newCondition) : GenePool(newSeed) {
	init(newPopulationSize, templateIndividual, myMaxGenerations, numIterations, newModel, newCondition);
}

HierarchicalGenePool::~HierarchicalGenePool() {
	for (int i = 0; i < populationSize; i++) {
		delete(myPopulation[i]);
	}

	free(myPopulation);
	free(populationFitnesses);
}

void HierarchicalGenePool::init(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, GenerationModel * newModel, EndCondition * newCondition) {
	myPopulation = (Individual**)malloc(sizeof(Individual*)*newPopulationSize);

	populationFitnesses = (int*)malloc(sizeof(int)*newPopulationSize);

	populationSize = newPopulationSize;
        currentGeneration = 0;
	readOnce = false;

	maxGenerations = myMaxGenerations;
	numIterationsPerGeneration = numIterations;
	myModel = newModel;
	myCondition = newCondition;

        for (int i = 0; i < populationSize; i++) {
                myPopulation[i] = templateIndividual->makeRandomCopy();
        }

        optimumFound = false;

        evaluateFitnesses();
}

//Evaluates the fitnesses of the population of this particular GenePool
//Basically a convenience thing
void HierarchicalGenePool::evaluateFitnesses() {
	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = myPopulation[i]->checkFitness();
	}
}

//Evaluates the fitnesses of a given population of individuals
//Doesn't care what their genetic makeup is - uses their fitness functions
int * HierarchicalGenePool::evaluateFitnesses(Individual ** populationToEval, int populationToEvalSize) {
	int * populationToEvalFitnesses = (int*)malloc(sizeof(int)*populationToEvalSize);

	for (int i = 0; i < populationToEvalSize; i++) {
		populationToEvalFitnesses[i] = populationToEval[i]->checkFitness();
	}

	return populationToEvalFitnesses;
}

//When we need a specific individual
void * HierarchicalGenePool::getIndex(int index) {
	void * returnValue;

	returnValue = (void*)myPopulation[index];

	return returnValue;
}

void * HierarchicalGenePool::getFittest() {
	int fittestIndex;
	int fittestIndexFitness = 0;

	for (int i = 0; i < populationSize; i++) {
		if (populationFitnesses[i] > fittestIndexFitness) {
			fittestIndex = i;
			fittestIndexFitness = populationFitnesses[i];
		}
	}

	return (void*)myPopulation[fittestIndex];
}

//Run one generation
void HierarchicalGenePool::nextGeneration() {
	Individual ** newPopulation;

	if (currentGeneration < maxGenerations && optimumFound == false) {
		//Run the hierarchical component first - we're evolving
		//from the bottom up
		myPopulation[0]->runHierarchicalGenerations();

		//Re-evaluate the fitnesses to take the lower GenePools
		//running their generations into account
		evaluateFitnesses();

		newPopulation = myModel->breedMutateSelect(myPopulation, populationFitnesses, populationSize);

                currentGeneration += 1;

		//The new generation replaces the old
		for (int i = 0; i < populationSize; i++) {
			myPopulation[i] = newPopulation[i]->deepCopy();
			delete(newPopulation[i]);
		}

		free(newPopulation);

		if (myCondition != NULL) {
			for (int i = 0; i < populationSize && optimumFound == false; i++) {
				optimumFound = myCondition->checkCondition(myPopulation[i]);
			}
		}
	}
}

//For HGAs - if we want to run multiple generations of a lower-level gene pool
//for every one of a higher-level one, this is how
//Basically a loop wrapped around nextGeneration()
void HierarchicalGenePool::runGenerations() {
	int target = currentGeneration + numIterationsPerGeneration;

	for (int i = currentGeneration; i < target && i < maxGenerations && optimumFound == false; i++) {
		nextGeneration();
	}
}

void HierarchicalGenePool::sortPopulation() {
	myModel->sortPopulation(myPopulation, populationFitnesses, populationSize);
}

int HierarchicalGenePool::getHighestFitness() {
	return populationFitnesses[0];
}

string HierarchicalGenePool::toString() {
	string returnString = "";
	stringstream ss;
	string populationString;

	ss << "Population size: " << populationSize << "\n";

	for (int i = 0; i < populationSize; i++) {
		if (readOnce == false) {
			populationString = myPopulation[i]->toString();
		} else {
			populationString = myPopulation[i]->toGenomeString();
		}

		ss << "Member " << i << ": " << populationString << " Fitness: " << populationFitnesses[i] << "\n";
	}

	if (readOnce == false) {
        	ss << "Seed: " << seed << "\n";
	        ss << "Selection Info:\n" << myModel->toString();
	}

	readOnce = true;

	returnString = ss.str();

	return returnString;
}
