#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"
#include "HierLongestFragmentFitness.hpp"

using namespace std;

int main(void) {

	Individual * templateIndividual;

	//Setting up the first level (bitstring length = 2, genome length = 2)
	SelectionStrategy *** bottomLevelStrategies = (SelectionStrategy***)malloc(sizeof(SelectionStrategy**)*4);
	
	EvolutionarySystem *** bottomLevelModels = (EvolutionarySystem***)malloc(sizeof(EvolutionarySystem**)*4);

	CrossoverOperation *** bottomLevelCrossovers = (CrossoverOperation***)malloc(sizeof(CrossoverOperation**)*4);

	MutationOperation *** bottomLevelMutations = (MutationOperation***)malloc(sizeof(MutationOperation**)*4);

	FitnessPropagator * myPropagator = new DownPropagator();
	ToStringFunction * RRToString = new LongestFragmentToString();

	for (int i = 0; i < 4; i++) {

		bottomLevelStrategies[i] = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
		bottomLevelModels[i] = (EvolutionarySystem**)malloc(sizeof(EvolutionarySystem*)*4);
		bottomLevelCrossovers[i] = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);
		bottomLevelMutations[i] = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

		for (int k = 0; k < 4; k++) {
			bottomLevelStrategies[i][k] = new TournamentSelection(0.5);
			bottomLevelModels[i][k] = new GA(2, bottomLevelStrategies[i][k]);
			bottomLevelCrossovers[i][k] = new NPointCrossover(2);
			bottomLevelMutations[i][k] = new UniformMutation(0.2);
		}
	}

	int binaryDigits[] = {0,1};

	//The idiomatically correct way to set up an HGA is to have EACH
	//GeneNode, hierarchical or otherwise, constructed separately
	//Because of this, setting up the bottom level of a balanced tree like
	//this can become somewhat cumbersome
	//Unfortunately, an extra level of pointers is required for each
	//additional level in order to do it correctly
	//TODO: Write a wrapper class, or at least a series of static methods,
	//to do it automatically
	GeneNode **** baseGenes = (GeneNode****)malloc(sizeof(GeneNode***)*4);

	for (int i = 0; i < 4; i++) {
		baseGenes[i] = (GeneNode***)malloc(sizeof(GeneNode**)*4);
		
		for (int k = 0; k < 4; k++) {
			baseGenes[i][k] = (GeneNode**)malloc(sizeof(GeneNode*)*2);
			for (int c = 0; c < 2; c++) {
				baseGenes[i][k][c] = new LibraryNode<int>(binaryDigits, 2);
			}
		}
	}

	GeneNode *** firstLevelPools = (GeneNode***)malloc(sizeof(GeneNode**)*4);

	for (int i = 0; i < 4; i++) {

		firstLevelPools[i] = (GeneNode**)malloc(sizeof(GeneNode*)*4);

		for (int k = 0; k < 4; k++) {
			templateIndividual = new Individual(baseGenes[i][k], 2, bottomLevelCrossovers[i][k], bottomLevelMutations[i][k], NULL, RRToString);
			firstLevelPools[i][k] = new PopulationNode(4, templateIndividual, 100, 1, bottomLevelModels[i][k], NULL, myPropagator);

			delete(templateIndividual);
		}
	}

	//Setting up the second level (bitstring length = 8, genome length = 4)
	EvolutionarySystem ** secondLevelModels = (EvolutionarySystem**)malloc(sizeof(EvolutionarySystem*)*4);
	CrossoverOperation ** secondLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);
	MutationOperation ** secondLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);
	SelectionStrategy ** secondLevelStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy)*4);

	ToStringFunction * HierRRToString = new HierLongestFragmentToString();

	for (int i = 0; i < 4; i++) {
		secondLevelStrategies[i] = new TournamentSelection(0.5);
		secondLevelModels[i] = new GA(2, secondLevelStrategies[i]);
		secondLevelCrossovers[i] = new NPointCrossover(2);
		secondLevelMutations[i] = new UniformMutation(0.2);
	}

	GeneNode ** secondLevelPools = (GeneNode**)malloc(sizeof(GeneNode*)*4);

	for (int i = 0; i < 4; i++) {
		templateIndividual = new Individual(firstLevelPools[i], 4, secondLevelCrossovers[i], secondLevelMutations[i], NULL, HierRRToString);
		secondLevelPools[i] = new PopulationNode(8, templateIndividual, 100, 1, secondLevelModels[i], NULL, myPropagator);

		delete(templateIndividual);
	}

	//Setting up the top level (bitstring length = 32, genome length = 4)
	SelectionStrategy * topLevelStrategy = new TournamentSelection(0.5);
	EvolutionarySystem * topLevelModel = new GA(2, topLevelStrategy);
	FitnessFunction * topLevelFunction = new HierLongestFragmentFitness();
	CrossoverOperation * topLevelCrossover = new NPointCrossover(2);
	MutationOperation * topLevelMutation = new UniformMutation(0.2);

	templateIndividual = new Individual(secondLevelPools, 4, topLevelCrossover, topLevelMutation, topLevelFunction, HierRRToString);

	GeneNode * topLevelPool = new PopulationNode(8, templateIndividual, 100, 1, topLevelModel, NULL, myPropagator);

	topLevelPool->run(true);

	//We clean up from the top down
	delete(templateIndividual);
	delete(topLevelPool);
	delete(topLevelModel);
	delete(topLevelStrategy);
	delete(topLevelFunction);
	delete(HierRRToString);
	delete(topLevelCrossover);
	delete(topLevelMutation);

	//Cleaning up the middle (second) level
	for (int i = 0; i < 4; i++) {
		delete(secondLevelPools[i]);
		delete(secondLevelStrategies[i]);
		delete(secondLevelModels[i]);
		delete(secondLevelCrossovers[i]);
		delete(secondLevelMutations[i]);
	}

	free(secondLevelPools);
	free(secondLevelStrategies);
	free(secondLevelModels);
	free(secondLevelCrossovers);
	free(secondLevelMutations);

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			delete(bottomLevelStrategies[i][k]);
			delete(bottomLevelModels[i][k]);
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
		free(bottomLevelCrossovers[i]);
		free(bottomLevelMutations[i]);
		free(firstLevelPools[i]);
		free(baseGenes[i]);
	}

	free(bottomLevelStrategies);
	free(bottomLevelModels);
	free(bottomLevelCrossovers);
	free(bottomLevelMutations);
	free(firstLevelPools);
	free(baseGenes);

	delete(myPropagator);
	delete(RRToString);
}

