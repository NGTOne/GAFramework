#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

int main(void) {
	SelectionStrategy * myStrategy = new TournamentSelection(0.5, 4);

	//EvolutionarySystem * myEvolutionarySystem = new SSGA(2, myStrategy);
	EvolutionarySystem * myEvolutionarySystem = new ReplacingGA(myStrategy);

	EndCondition * myEndCondition = new FitnessMatchEnd(32);

	FitnessFunction * myFunction = new OneMaxFitness();
	ToStringFunction * myToString = new OneMaxToString();
	CrossoverOperation * myCrossover = new NPointCrossover(2);
	MutationOperation * myMutation = new UniformMutation(0.2);

	FitnessPropagator * myPropagator = new NonPropagator();

	GeneNode ** baseGenes = (GeneNode**)malloc(sizeof(GeneNode*)*32);

	for (int i = 0; i < 32; i++) {
		baseGenes[i] = new IntLocus(0, 1);
	}

	Individual * templateIndividual = new Individual(baseGenes, 32, myCrossover, myMutation, myFunction, myToString);

	PopulationNode * node = new PopulationNode(64, templateIndividual, 100, 1, myEvolutionarySystem, myEndCondition, myPropagator);

	delete(templateIndividual);

	HierarchicalEA ea(100);
	ea.addNode(node, "P1", true, true);
	ea.setEvolutionOrder({"P1"});
	ea.run(true);

	delete(node);
	for (int i = 0; i < 32; i++) {
		delete(baseGenes[i]);
	}

	delete(myEvolutionarySystem);
	delete(myMutation);
	delete(myCrossover);
	delete(myStrategy);
	delete(myEndCondition);
	delete(myFunction);
	delete(myToString);
	delete(myPropagator);

	free(baseGenes);
}

