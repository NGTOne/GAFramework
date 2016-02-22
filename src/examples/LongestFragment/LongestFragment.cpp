#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"

using namespace std;

int main(void) {
	SelectionStrategy * myStrategy = new TournamentSelection(0.5);

	EvolutionarySystem * myModel = new GA(2, myStrategy);

	FitnessFunction * myFunction = new LongestFragmentFitness();
	ToStringFunction * myToString = new LongestFragmentToString();
	CrossoverOperation * myCrossover = new NPointCrossover(2);
	MutationOperation * myMutation = new UniformMutation(0.2);

	FitnessPropagator * myPropagator = new NonPropagator();

	int binaryDigits[] = {0,1};

	GeneNode ** baseGenes = (GeneNode**)malloc(sizeof(GeneNode*)*64);

	for (int i = 0; i < 64; i++) {
		baseGenes[i] = new LibraryNode<int>(binaryDigits, 2);
	}

	Individual * templateIndividual = new Individual(baseGenes, 64, myCrossover, myMutation, myFunction, myToString);

	PopulationNode * topLevelPool = new PopulationNode(128, templateIndividual, 100, 1, myModel, NULL, myPropagator);

	delete(templateIndividual);

	HierarchicalEA ea(100);
	ea.addNode(topLevelPool, "P1", true, true);
	ea.setEvolutionOrder({"P1"});
	ea.run(true);

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

