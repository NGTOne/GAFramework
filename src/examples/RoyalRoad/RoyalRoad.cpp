#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "RoyalRoadFitness.hpp"

using namespace std;

int main(void) {
	SelectionStrategy * myStrategy = new TournamentSelection(0.5);

	GenerationModel * myModel = new GAGeneration(2, myStrategy);

	FitnessFunction * myFunction = new RoyalRoadFitness();
	ToStringFunction * myToString = new RoyalRoadToString();
	CrossoverOperation * myCrossover = new NPointCrossover(2);
	MutationOperation * myMutation = new UniformMutation(0.2);

	FitnessPropagator * myPropagator = new NonPropagator();

	int binaryDigits[] = {0,1};

	GenePool ** baseGenes = (GenePool**)malloc(sizeof(GenePool*)*64);

	for (int i = 0; i < 64; i++) {
		baseGenes[i] = new LibraryNode<int>(binaryDigits, 2);
	}

	Individual * templateIndividual = new Individual(baseGenes, 64, myCrossover, myMutation, myFunction, myToString);

	HierarchicalGenePool * topLevelPool = new HierarchicalGenePool(128, templateIndividual, 100, 1, myModel, NULL, myPropagator);

	delete(templateIndividual);
	
	topLevelPool->run(true);

	delete(topLevelPool);
	for (int i = 0; i < 64; i++) {
		delete(baseGenes[i]);
	}

	delete(myModel);
	delete(myMutation);
	delete(myCrossover);
	delete(myStrategy);
	delete(myFunction);
	delete(myToString);
	delete(myPropagator);

	free(baseGenes);
}

