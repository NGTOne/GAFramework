#include <cstdio>
#include <iostream>
#include "NonHierarchicalGenePool.h"
#include "HierarchicalGenePool.h"
#include "BitwiseMutation.h"
#include "TwoPointCrossover.h"
#include "TournamentSelection.h"
#include "1maxFitness.h"
#include "Hier1maxFitness.h"

int main(void) {

	SelectionStrategy ** bottomLevelStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
	
	FitnessFunction ** bottomLevelFunctions = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);

	CrossoverOperation ** bottomLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);

	MutationOperation ** bottomLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

	for (int i = 0; i < 4; i++) {
		bottomLevelStrategies[i] = new TournamentSelection(0.5, 2);
		bottomLevelFunctions[i] = new OneMaxFitness();
		bottomLevelCrossovers[i] = new TwoPointCrossover();
		bottomLevelMutations[i] = new BitwiseMutation(0.5);
	}

	int binaryDigits[] = {0,1};

	//An array of arrays of binary GenePools - because each of the 4
	//subtrees will have the same type of GenePools at the bottom
	GenePool *** baseGenes = (GenePool***)malloc(sizeof(GenePool**)*4);

	//The four "mid-level" pools - a step between the base pools and the
	//top level
        GenePool ** bottomLevelPools = (GenePool**)malloc(sizeof(GenePool*)*4);

	for (int i = 0; i < 4; i++) {
		baseGenes[i] = (GenePool**)malloc(sizeof(GenePool*)*8);

		for (int k = 0; k < 8; k++) {
			baseGenes[i][k] = new NonHierarchicalGenePool<int>(binaryDigits, 2);
		}

		Individual * bottomLevelTemplateIndividual = new Individual(baseGenes[i], 8, bottomLevelCrossovers[i], bottomLevelMutations[i], bottomLevelFunctions[i]);

		bottomLevelPools[i] = new HierarchicalGenePool(8, bottomLevelTemplateIndividual, 100, 1, bottomLevelStrategies[i]);
	}

	CrossoverOperation * topLevelCrossover = new TwoPointCrossover();
	MutationOperation * topLevelMutation = new BitwiseMutation(0.5);
	FitnessFunction * topLevelFunction = new HierOneMaxFitness();
	SelectionStrategy * topLevelStrategy = new TournamentSelection(0.5, 2);

	Individual * templateIndividual = new Individual(bottomLevelPools, 4, topLevelCrossover, topLevelMutation, topLevelFunction);

	HierarchicalGenePool * topLevelPool = new HierarchicalGenePool(32, templateIndividual, 100, 1, topLevelStrategy);

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

