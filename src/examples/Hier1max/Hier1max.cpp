#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"
#include "Hier1maxFitness.hpp"

using namespace std;

int main(void) {

	SelectionStrategy ** bottomLevelStrategies = (SelectionStrategy**)malloc(sizeof(SelectionStrategy*)*4);
	
	GenerationModel ** bottomLevelModels = (GenerationModel**)malloc(sizeof(GenerationModel*)*4);

	FitnessFunction ** bottomLevelFunctions = (FitnessFunction**)malloc(sizeof(FitnessFunction*)*4);

	CrossoverOperation ** bottomLevelCrossovers = (CrossoverOperation**)malloc(sizeof(CrossoverOperation*)*4);

	MutationOperation ** bottomLevelMutations = (MutationOperation**)malloc(sizeof(MutationOperation*)*4);

	FitnessPropagator * myPropagator = new NonPropagator();
	ToStringFunction * bottomLevelToString = new OneMaxToString();

	for (int i = 0; i < 4; i++) {
		bottomLevelStrategies[i] = new TournamentSelection(0.5);
		bottomLevelModels[i] = new GAGeneration(2, bottomLevelStrategies[i]);
		bottomLevelFunctions[i] = new OneMaxFitness();
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
			baseGenes[i][k] = new LibraryNode<int>(binaryDigits, 2);
		}

		Individual * bottomLevelTemplateIndividual = new Individual(baseGenes[i], 8, bottomLevelCrossovers[i], bottomLevelMutations[i], bottomLevelFunctions[i], bottomLevelToString);

		bottomLevelPools[i] = new HierarchicalGenePool(8, bottomLevelTemplateIndividual, 100, 1, bottomLevelModels[i], NULL, myPropagator);

		delete(bottomLevelTemplateIndividual);
	}

	CrossoverOperation * topLevelCrossover = new NPointCrossover(2);
	MutationOperation * topLevelMutation = new UniformMutation(0.2);
	FitnessFunction * topLevelFunction = new HierOneMaxFitness();
	ToStringFunction * topLevelToString = new HierOneMaxToString();
	SelectionStrategy * topLevelStrategy = new TournamentSelection(0.5);
	GenerationModel * topLevelModel = new GAGeneration(2, topLevelStrategy);
	EndCondition * topLevelCondition = new FitnessMatchEnd(32);

	Individual * templateIndividual = new Individual(bottomLevelPools, 4, topLevelCrossover, topLevelMutation, topLevelFunction, topLevelToString);

	HierarchicalGenePool * topLevelPool = new HierarchicalGenePool(32, templateIndividual, 100, 1, topLevelModel, topLevelCondition, myPropagator);

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
	delete(topLevelCondition);
	delete(templateIndividual);
	delete(topLevelPool);

}

