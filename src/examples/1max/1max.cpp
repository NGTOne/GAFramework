#include <cstdio>
#include "NonHierarchicalGenePool.h"
#include "HierarchicalGenePool.h"
#include "BitwiseMutation.h"
#include "TwoPointCrossover.h"
#include "TournamentSelection.h"
#include "1maxFitness.h"

int main(void) {
	TournamentSelection myStrategy();

	FitnessFunction * myFunction = new OneMaxFitness();
	CrossoverOperation * myCrossover = new TwoPointCrossover();
	MutationOperation * myMutation = new BitwiseMutation();

	int binaryDigits[] = {0,1};

	NonHierarchicalGenePool<int> baseGenes[32];

	for (int i = 0; i < 32; i++) {
		baseGenes[i] =  NonHierarchicalGenePool<int>(binaryDigits, 2);
	}

	Individual templateIndividual(baseGenes, *myCrossover, *myMutation, *myFunction);

	HierarchicalGenePool topLevelPool(templateIndividual, 64, 100, 1);

	for (int i = 0; i < 1000; i++) {
		topLevelPool.runGenerations();
	}
}
