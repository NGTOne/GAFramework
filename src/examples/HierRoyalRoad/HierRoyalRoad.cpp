#include <cstdio>
#include <iostream>
#include <libGAFramework/GAFramework.hpp>
#include "RoyalRoadFitness.hpp"
#include "HierRoyalRoadFitness.hpp"

int main(void) {

	SelectionStrategy ** bottomLevelStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
	
	GenerationModel ** bottomLevelModels = (GenerationModel**)malloc(sizeof(GenerationModel*)*4);

	FitnessFunction ** bottomLevelFunctions = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);

	CrossoverOperation ** bottomLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);

	MutationOperation ** bottomLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

	FitnessPropagator * myPropagator = new NonPropagator();

	for (int i = 0; i < 4; i++) {
		bottomLevelStrategies[i] = new TournamentSelection(0.5);
		bottomLevelModels[i] = new GAGeneration(2, bottomLevelStrategies[i]);
		bottomLevelFunctions[i] = new RoyalRoadFitness();
		bottomLevelCrossovers[i] = new NPointCrossover(2);
		bottomLevelMutations[i] = new UniformMutation(0.2);
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

		bottomLevelPools[i] = new HierarchicalGenePool(8, bottomLevelTemplateIndividual, 100, 1, bottomLevelModels[i], NULL, myPropagator);
	}

	CrossoverOperation * topLevelCrossover = new NPointCrossover(2);
	MutationOperation * topLevelMutation = new UniformMutation(0.2);
	FitnessFunction * topLevelFunction = new HierRoyalRoadFitness();
	SelectionStrategy * topLevelStrategy = new TournamentSelection(0.5);
	GenerationModel * topLevelModel = new GAGeneration(2, topLevelStrategy);

	Individual * templateIndividual = new Individual(bottomLevelPools, 4, topLevelCrossover, topLevelMutation, topLevelFunction);

	HierarchicalGenePool * topLevelPool = new HierarchicalGenePool(32, templateIndividual, 100, 1, topLevelModel, NULL, myPropagator);

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

