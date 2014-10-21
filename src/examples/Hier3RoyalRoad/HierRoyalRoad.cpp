#include <cstdio>
#include <iostream>
#include <libGAFramework/GAFramework.hpp>
#include "RoyalRoadFitness.hpp"
#include "HierRoyalRoadFitness.hpp"

using namespace std;

int main(void) {

	Individual * templateIndividual;

	//Setting up the first level (bitstring length = 2, genome length = 2)
	SelectionStrategy *** bottomLevelStrategies = (SelectionStrategy***)malloc(sizeof(SelectionStrategy**)*4);
	
	GenerationModel *** bottomLevelModels = (GenerationModel***)malloc(sizeof(GenerationModel**)*4);

	FitnessFunction *** bottomLevelFunctions = (FitnessFunction***)malloc(sizeof(FitnessFunction**)*4);

	CrossoverOperation *** bottomLevelCrossovers = (CrossoverOperation***)malloc(sizeof(CrossoverOperation**)*4);

	MutationOperation *** bottomLevelMutations = (MutationOperation***)malloc(sizeof(MutationOperation**)*4);

	ToStringFunction * bottomLevelToString = new RoyalRoadToString();

	FitnessPropagator * myPropagator = new NonPropagator();

	for (int i = 0; i < 4; i++) {

		bottomLevelStrategies[i] = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
		bottomLevelModels[i] = (GenerationModel**)malloc(sizeof(GenerationModel*)*4);
		bottomLevelFunctions[i] = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);
		bottomLevelCrossovers[i] = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);
		bottomLevelMutations[i] = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

		for (int k = 0; k < 4; k++) {
			bottomLevelStrategies[i][k] = new TournamentSelection(0.5);
			bottomLevelModels[i][k] = new GAGeneration(2, bottomLevelStrategies[i][k]);
			bottomLevelFunctions[i][k] = new RoyalRoadFitness();
			bottomLevelCrossovers[i][k] = new NPointCrossover(2);
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
			templateIndividual = new Individual(baseGenes[i][k], 2, bottomLevelCrossovers[i][k], bottomLevelMutations[i][k], bottomLevelFunctions[i][k], bottomLevelToString);
			firstLevelPools[i][k] = new HierarchicalGenePool(4, templateIndividual, 100, 1, bottomLevelModels[i][k], NULL, myPropagator);

			delete(templateIndividual);
		}
	}

	//Setting up the second level (bitstring length = 8, genome length = 4)
	SelectionStrategy ** secondLevelStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
	GenerationModel ** secondLevelModels = (GenerationModel**)malloc(sizeof(GenerationModel*)*4);
	FitnessFunction ** secondLevelFunctions = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);
	CrossoverOperation ** secondLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);
	MutationOperation ** secondLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

	ToStringFunction * secondLevelToString = new HierRoyalRoadToString();

	for (int i = 0; i < 4; i++) {
		secondLevelStrategies[i] = new TournamentSelection(0.5);
		secondLevelModels[i] = new GAGeneration(2, secondLevelStrategies[i]);
		secondLevelFunctions[i] = new HierRoyalRoadFitness();
		secondLevelCrossovers[i] = new NPointCrossover(2);
		secondLevelMutations[i] = new UniformMutation(0.2);
	}

	GenePool ** secondLevelPools = (GenePool**)malloc(sizeof(GenePool*)*4);

	for (int i = 0; i < 4; i++) {
		templateIndividual = new Individual(firstLevelPools[i], 4, secondLevelCrossovers[i], secondLevelMutations[i], secondLevelFunctions[i], secondLevelToString);
		secondLevelPools[i] = new HierarchicalGenePool(8, templateIndividual, 100, 1, secondLevelModels[i], NULL, myPropagator);

		delete(templateIndividual);
	}

	//Setting up the top level (bitstring length = 32, genome length = 4)
	SelectionStrategy * topLevelStrategy = new TournamentSelection(0.5);
	GenerationModel * topLevelModel = new GAGeneration(2, topLevelStrategy);
	FitnessFunction * topLevelFunction = new HierRoyalRoadFitness();
	ToStringFunction * topLevelToString = new HierRoyalRoadToString();
	CrossoverOperation * topLevelCrossover = new NPointCrossover(2);
	MutationOperation * topLevelMutation = new UniformMutation(0.2);

	templateIndividual = new Individual(secondLevelPools, 4, topLevelCrossover, topLevelMutation, topLevelFunction, topLevelToString);

	GenePool * topLevelPool = new HierarchicalGenePool(8, templateIndividual, 100, 1, topLevelModel, NULL, myPropagator);

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

	//We clean up from the top down
	delete(templateIndividual);
	delete(topLevelPool);
	delete(topLevelModel);
	delete(topLevelStrategy);
	delete(topLevelFunction);
	delete(topLevelToString);
	delete(topLevelCrossover);
	delete(topLevelMutation);

	//Cleaning up the middle (second) level
	for (int i = 0; i < 4; i++) {
		delete(secondLevelPools[i]);
		delete(secondLevelStrategies[i]);
		delete(secondLevelModels[i]);
		delete(secondLevelFunctions[i]);
		delete(secondLevelCrossovers[i]);
		delete(secondLevelMutations[i]);
	}

	free(secondLevelPools);
	free(secondLevelStrategies);
	free(secondLevelModels);
	free(secondLevelFunctions);
	free(secondLevelCrossovers);
	free(secondLevelMutations);

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			delete(bottomLevelStrategies[i][k]);
			delete(bottomLevelModels[i][k]);
			delete(bottomLevelFunctions[i][k]);
			delete(bottomLevelCrossovers[i][k]);
			delete(bottomLevelMutations[i][k]);
			delete(firstLevelPools[i][k]);

			for (int c = 0; c < 2; c++) {
				delete(baseGenes[i][k][c]);
			}
			free(baseGenes[i][k]);
		}

		free(bottomLevelStrategies[i]);
		free(bottomLevelModels[i]);
		free(bottomLevelFunctions[i]);
		free(bottomLevelCrossovers[i]);
		free(bottomLevelMutations[i]);
		free(firstLevelPools[i]);
		free(baseGenes[i]);
	}

	free(bottomLevelStrategies);
	free(bottomLevelModels);
	free(bottomLevelFunctions);
	free(bottomLevelCrossovers);
	free(bottomLevelMutations);
	free(firstLevelPools);
	free(baseGenes);

	delete(myPropagator);
	delete(bottomLevelToString);
	delete(secondLevelToString);
}
