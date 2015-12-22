#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "RoyalRoadFitness.hpp"
#include "HierRoyalRoadFitness.hpp"

using namespace std;

int main(void) {

	SelectionStrategy ** bottomLevelStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
	
	GenerationModel ** bottomLevelModels = (GenerationModel**)malloc(sizeof(GenerationModel*)*4);

	FitnessFunction ** bottomLevelFunctions = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);

	CrossoverOperation ** bottomLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);

	MutationOperation ** bottomLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

	ToStringFunction * bottomLevelToString = new RoyalRoadToString();

	FitnessPropagator * myPropagator = new NonPropagator();

	for (int i = 0; i < 4; i++) {
		bottomLevelStrategies[i] = new TournamentSelection(0.5);
		bottomLevelModels[i] = new GAGeneration(2, bottomLevelStrategies[i]);
		bottomLevelFunctions[i] = new RoyalRoadFitness();
		bottomLevelCrossovers[i] = new NPointCrossover(2);
		bottomLevelMutations[i] = new UniformMutation(0.2);
	}

	int binaryDigits[] = {0,1};

	//An array of arrays of binary GeneNodes - because each of the 4
	//subtrees will have the same type of GeneNodes at the bottom
	GeneNode *** baseGenes = (GeneNode***)malloc(sizeof(GeneNode**)*4);

	//The four "mid-level" pools - a step between the base pools and the
	//top level
        GeneNode ** bottomLevelPools = (GeneNode**)malloc(sizeof(GeneNode*)*4);

	for (int i = 0; i < 4; i++) {
		baseGenes[i] = (GeneNode**)malloc(sizeof(GeneNode*)*8);

		for (int k = 0; k < 8; k++) {
			baseGenes[i][k] = new LibraryNode<int>(binaryDigits, 2);
		}

		Individual * bottomLevelTemplateIndividual = new Individual(baseGenes[i], 8, bottomLevelCrossovers[i], bottomLevelMutations[i], bottomLevelFunctions[i], bottomLevelToString);

		bottomLevelPools[i] = new PopulationNode(8, bottomLevelTemplateIndividual, 100, 1, bottomLevelModels[i], NULL, myPropagator);

		delete(bottomLevelTemplateIndividual);
	}

	CrossoverOperation * topLevelCrossover = new NPointCrossover(2);
	MutationOperation * topLevelMutation = new UniformMutation(0.2);
	FitnessFunction * topLevelFunction = new HierRoyalRoadFitness();
	ToStringFunction * topLevelToString = new HierRoyalRoadToString();
	SelectionStrategy * topLevelStrategy = new TournamentSelection(0.5);
	GenerationModel * topLevelModel = new GAGeneration(2, topLevelStrategy);

	Individual * templateIndividual = new Individual(bottomLevelPools, 4, topLevelCrossover, topLevelMutation, topLevelFunction, topLevelToString);

	PopulationNode * topLevelPool = new PopulationNode(32, templateIndividual, 100, 1, topLevelModel, NULL, myPropagator);

	topLevelPool->run(true);

	delete(myPropagator);
	delete(bottomLevelToString);

	for (int i = 0; i < 4; i++) {
		delete(bottomLevelStrategies[i]);
		delete(bottomLevelModels[i]);
		delete(bottomLevelFunctions[i]);
		delete(bottomLevelCrossovers[i]);
		delete(bottomLevelMutations[i]);
		delete(bottomLevelPools[i]);

		for (int k = 0; k < 8; k++) {
			delete(baseGenes[i][k]);
		}
		free(baseGenes[i]);
	}

	free(bottomLevelStrategies);
	free(bottomLevelModels);
	free(bottomLevelFunctions);
	free(bottomLevelCrossovers);
	free(bottomLevelMutations);
	free(bottomLevelPools);
	free(baseGenes);

	delete(topLevelCrossover);
	delete(topLevelMutation);
	delete(topLevelFunction);
	delete(topLevelToString);
	delete(topLevelStrategy);
	delete(topLevelModel);
	delete(templateIndividual);
	delete(topLevelPool);
}

