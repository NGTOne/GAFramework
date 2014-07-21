#include <cstdio>
#include <iostream>
#include <libGAFramework/GAFramework.hpp>
#include "1maxFitness.hpp"

int main(void) {
	SelectionStrategy * myStrategy = new TournamentSelection(0.5);

	GenerationModel * myGenerationModel = new GAGeneration(2, myStrategy);

	EndCondition * myEndCondition = new FitnessMatchEnd(32);

	FitnessFunction * myFunction = new OneMaxFitness();
	ToStringFunction * myToString = new OneMaxToString();
	CrossoverOperation * myCrossover = new NPointCrossover(2);
	MutationOperation * myMutation = new UniformMutation(0.2);

	FitnessPropagator * myPropagator = new NonPropagator();

	int binaryDigits[] = {0,1};

	GenePool ** baseGenes = (GenePool**)malloc(sizeof(GenePool*)*32);

	for (int i = 0; i < 32; i++) {
		baseGenes[i] = new NonHierarchicalGenePool<int>(binaryDigits, 2);
	}

	Individual * templateIndividual = new Individual(baseGenes, 32, myCrossover, myMutation, myFunction, myToString);

	HierarchicalGenePool * topLevelPool = new HierarchicalGenePool(64, templateIndividual, 100, 1, myGenerationModel, myEndCondition, myPropagator);

	delete(templateIndividual);
	
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

	delete(topLevelPool);
	for (int i = 0; i < 32; i++) {
		delete(baseGenes[i]);
	}

	free(baseGenes);
}

