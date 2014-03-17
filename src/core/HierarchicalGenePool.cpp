//This is a dual-purpose class for gene pools - it serves as a "base"
//GA, and also as a gene pool for individuals in hierarchical GAs
//Since these functions are, by and large, very similar, they can be
//combined together into one class

#include "HierarchicalGenePool.h"

using namespace std;

//If we don't know the optimum
HierarchicalGenePool::HierarchicalGenePool(int populationSize, Individual templateIndividual, int myMaxGenerations, int numIterations, SelectionStrategy newStrategy) : myStrategy(newStrategy) {
	myPopulation = (Individual*)malloc(sizeof(Individual)*populationSize);;
	currentGeneration = 0;

	for (int i = 0; i < populationSize; i++) {
		myPopulation[i] = templateIndividual.makeRandomCopy();
	}
	
	optimumFound = false;
	knownOptimum = false;
	maxGenerations = myMaxGenerations;
	numIterationsPerGeneration = numIterations;

	evaluateFitnesses();

	sortPopulation(myPopulation, populationFitnesses, populationSize);
}

//If we do know the optimum
HierarchicalGenePool::HierarchicalGenePool(int populationSize, Individual templateIndividual, int myMaxGenerations, int numIterations, SelectionStrategy newStrategy, int optimalGenome[]) : myStrategy(newStrategy) {
	myPopulation = (Individual*)malloc(sizeof(Individual)*populationSize);
	currentGeneration = 0;

	for (int i = 0; i < populationSize; i++) {
                myPopulation[i] = templateIndividual.makeRandomCopy();
        }

	optimumFound = false;
        knownOptimum = true;
        maxGenerations = myMaxGenerations;
        numIterationsPerGeneration = numIterations;

	optimumGenome = optimalGenome;

	Individual optimumIndividual = templateIndividual.makeSpecifiedCopy(optimalGenome);

	optimumFitness = optimumIndividual.checkFitness();

	evaluateFitnesses();

	sortPopulation(myPopulation, populationFitnesses, populationSize);
}

//Evaluates the fitnesses of the population of this particular GenePoo
//Basically a convenience thing
void HierarchicalGenePool::evaluateFitnesses() {
	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = myPopulation[i].checkFitness();
	}
}

//Evaluates the fitnesses of a given population of individuals
//Doesn't care what their genetic makeup is - uses their fitness functions
int * HierarchicalGenePool::evaluateFitnesses(Individual populationToEval[], int populationToEvalSize) {
	int * populationToEvalFitnesses = (int*)malloc(sizeof(int)*populationToEvalSize);

	for (int i = 0; i < populationToEvalSize; i++) {
		populationToEvalFitnesses[i] = populationToEval[i].checkFitness();
	}

	return populationToEvalFitnesses;
}

//When we need a specific individual
void * HierarchicalGenePool::getIndex(int index) {
	void * returnValue;

	returnValue = (void*)&myPopulation[index];

	return returnValue;
}

//Run one generation
void HierarchicalGenePool::nextGeneration() {
	Individual * newPopulation;

	if (currentGeneration < maxGenerations && (knownOptimum == false || (optimumFound != true && knownOptimum == true))) {
		//Run the hierarchical component first - we're evolving
		//from the bottom up
		myPopulation[0].runHierarchicalGenerations();

		newPopulation = myStrategy.breedMutateSelect(myPopulation, populationFitnesses, populationSize);

                currentGeneration += 1;

		if (knownOptimum == true) {
                       	for (int i = 0; i < populationSize && optimumFound == false; i++) {
                               	//TODO: make this more approximate
                               	if (populationFitnesses[i] == optimumFitness) {
                                       	optimumFound = true;
                               	}
                       	}
		}
		
		//The new generation replaces the old
		for (int i = 0; i < populationSize; i++) {
			myPopulation[i] = newPopulation[i];
		}
	}
}

//For HGAs - if we want to run multiple generations of a lower-level gene pool
//for every one of a higher-level one, this is how
//Basically a loop wrapped around nextGeneration()
void HierarchicalGenePool::runGenerations() {
	int target = currentGeneration + numIterationsPerGeneration;

	for (int i = currentGeneration; i <= target && i <= maxGenerations && optimumFound == false; i++) {
		nextGeneration();
	}
}

Individual * HierarchicalGenePool::sortPopulation(Individual initialPopulation[], int initialFitnesses[], int populationSize) {
	//TODO: Make more efficient
	Individual tempIndividual;
	int temp;

	for (int i = 0; i < populationSize; i++) {
		for (int k = 0; k < populationSize; k++) {
			if (initialFitnesses[k] > initialFitnesses[i]) {
				tempIndividual = initialPopulation[i];
				temp = initialFitnesses[i];

				initialPopulation[i] = initialPopulation[k];
				initialFitnesses[i] = initialFitnesses[k];

				initialPopulation[k] = tempIndividual;
				initialFitnesses[i] = temp;
			}
		}
	}

	return initialPopulation;
}
