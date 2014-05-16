#include <cstdio>
#include <iostream>
#include <libGAFramework/GAFramework.hpp>
#include "RoyalRoadFitness.hpp"

int main(void) {
	SelectionStrategy * myStrategy = new TournamentSelection(0.5);

	GenerationModel * myModel = new GAGeneration(2, myStrategy);

	FitnessFunction * myFunction = new RoyalRoadFitness();
	CrossoverOperation * myCrossover = new NPointCrossover(2);
	MutationOperation * myMutation = new UniformMutation(0.2);

	EndCondition * myCondition = new FitnessMatchEnd(32);

	int binaryDigits[] = {0,1};

	GenePool ** baseGenes = (GenePool**)malloc(sizeof(GenePool*)*64);

	for (int i = 0; i < 64; i++) {
		baseGenes[i] = new NonHierarchicalGenePool<int>(binaryDigits, 2);
	}

	Individual * templateIndividual = new Individual(baseGenes, 64, myCrossover, myMutation, myFunction);

	HierarchicalGenePool * topLevelPool = new HierarchicalGenePool(128, templateIndividual, 100, 1, myModel, myCondition);

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

