#include <cstdio>
#include <iostream>
#include "NonHierarchicalGenePool.h"
#include "HierarchicalGenePool.h"
#include "UniformMutation.h"
#include "TwoPointCrossover.h"
#include "TournamentSelection.h"
#include "GAGeneration.h"
#include "1maxFitness.h"

int main(void) {
	SelectionStrategy * myStrategy = new TournamentSelection(0.5);

	GenerationModel * myGenerationModel = new GAGeneration(2, myStrategy);

	FitnessFunction * myFunction = new OneMaxFitness();
	CrossoverOperation * myCrossover = new TwoPointCrossover();
	MutationOperation * myMutation = new UniformMutation(0.2);

	int binaryDigits[] = {0,1};

	GenePool ** baseGenes = (GenePool**)malloc(sizeof(GenePool*)*32);

	for (int i = 0; i < 32; i++) {
		baseGenes[i] = new NonHierarchicalGenePool<int>(binaryDigits, 2);
	}

	Individual * templateIndividual = new Individual(baseGenes, 32, myCrossover, myMutation, myFunction);

	HierarchicalGenePool * topLevelPool = new HierarchicalGenePool(64, templateIndividual, 100, 1, myGenerationModel);

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

