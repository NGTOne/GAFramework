#include <cstdio>
#include <iostream>
#include "NonHierarchicalGenePool.h"
#include "HierarchicalGenePool.h"
#include "UniformMutation.h"
#include "TwoPointCrossover.h"
#include "TournamentSelection.h"
#include "RoyalRoadFitness.h"
#include "HierRoyalRoadFitness.h"

int main(void) {

	Individual * templateIndividual;

	//Setting up the first level (bitstring length = 2, genome length = 2)
	SelectionStrategy *** bottomLevelStrategies = (SelectionStrategy***)malloc(sizeof(SelectionStrategy**)*4);
	
	FitnessFunction *** bottomLevelFunctions = (FitnessFunction***)malloc(sizeof(FitnessFunction**)*4);

	CrossoverOperation *** bottomLevelCrossovers = (CrossoverOperation***)malloc(sizeof(CrossoverOperation**)*4);

	MutationOperation *** bottomLevelMutations = (MutationOperation***)malloc(sizeof(MutationOperation**)*4);

	for (int i = 0; i < 4; i++) {

		bottomLevelStrategies[i] = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
		bottomLevelFunctions[i] = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);
		bottomLevelCrossovers[i] = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);
		bottomLevelMutations[i] = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

		for (int k = 0; k < 4; k++) {
			bottomLevelStrategies[i][k] = new TournamentSelection(0.5, 2, 'g');
			bottomLevelFunctions[i][k] = new RoyalRoadFitness();
			bottomLevelCrossovers[i][k] = new TwoPointCrossover();
			bottomLevelMutations[i][k] = new UniformMutation(0.2);
		}
	}

	int binaryDigits[] = {0,1};

	//The idiomatically correct way to set up an HGA is to have EACH
	//GenePool, hierarchical or otherwise, constructed separately
	//Because of this, setting up the bottom level of a balanced tree like
	//this can become somewhat cumbersome
	//Unfortunately, an extra level of pointers is required for each
	//additional level in order to do it correctly
	//TODO: Write a wrapper class, or at least a series of static methods,
	//to do it automatically
	GenePool **** baseGenes = (GenePool****)malloc(sizeof(GenePool***)*4);

	for (int i = 0; i < 4; i++) {
		baseGenes[i] = (GenePool***)malloc(sizeof(GenePool**)*4);
		
		for (int k = 0; k < 4; k++) {
			baseGenes[i][k] = (GenePool**)malloc(sizeof(GenePool*)*2);
			for (int c = 0; c < 2; c++) {
				baseGenes[i][k][c] = new NonHierarchicalGenePool<int>(binaryDigits, 2);
			}
		}
	}

	GenePool *** firstLevelPools = (GenePool***)malloc(sizeof(GenePool**)*4);

	for (int i = 0; i < 4; i++) {

		firstLevelPools[i] = (GenePool**)malloc(sizeof(GenePool*)*4);

		for (int k = 0; k < 4; k++) {
			templateIndividual = new Individual(baseGenes[i][k], 2, bottomLevelCrossovers[i][k], bottomLevelMutations[i][k], bottomLevelFunctions[i][k]);
			firstLevelPools[i][k] = new HierarchicalGenePool(4, templateIndividual, 100, 1, bottomLevelStrategies[i][k]);
		}
	}

	//Setting up the second level (bitstring length = 8, genome length = 4)
	SelectionStrategy ** secondLevelStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
	FitnessFunction ** secondLevelFunctions = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);
	CrossoverOperation ** secondLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);
	MutationOperation ** secondLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

	for (int i = 0; i < 4; i++) {
		secondLevelStrategies[i] = new TournamentSelection(0.5, 2, 'g');
		secondLevelFunctions[i] = new HierRoyalRoadFitness();
		secondLevelCrossovers[i] = new TwoPointCrossover();
		secondLevelMutations[i] = new UniformMutation(0.2);
	}

	GenePool ** secondLevelPools = (GenePool**)malloc(sizeof(GenePool*)*4);

	for (int i = 0; i < 4; i++) {
		templateIndividual = new Individual(firstLevelPools[i], 4, secondLevelCrossovers[i], secondLevelMutations[i], secondLevelFunctions[i]);
		secondLevelPools[i] = new HierarchicalGenePool(8, templateIndividual, 100, 1, secondLevelStrategies[i]);
	}

	//Setting up the top level (bitstring length = 32, genome length = 4)
	SelectionStrategy * topLevelStrategy = new TournamentSelection(0.5, 2, 'g');
	FitnessFunction * topLevelFunction = new HierRoyalRoadFitness();
	CrossoverOperation * topLevelCrossover = new TwoPointCrossover();
	MutationOperation * topLevelMutation = new UniformMutation(0.2);

	templateIndividual = new Individual(secondLevelPools, 4, topLevelCrossover, topLevelMutation, topLevelFunction);

	GenePool * topLevelPool = new HierarchicalGenePool(8, templateIndividual, 100, 1, topLevelStrategy);

	printf("Before:\n");
	cout << topLevelPool->toString();
	for (int i = 0; i < 120; i++) {
		cout << "-----------------------------------------------------------------\n";
		topLevelPool->runGenerations();
		cout << "After generation " << i << ":\n";
		cout << topLevelPool->toString();
	}

	cout << "--------------------------------------------------------------------------\nAfter:\n";
	cout << topLevelPool->toString();
}

