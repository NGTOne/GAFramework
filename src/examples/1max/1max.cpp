#include <cstdio>
#include <iostream>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

int main(void) {
	SelectionStrategy * myStrategy = new TournamentSelection(0.5);

	//GenerationModel * myGenerationModel = new SSGAGeneration(2, myStrategy);
	GenerationModel * myGenerationModel = new ReplacingGAGeneration(myStrategy);

	EndCondition * myEndCondition = new FitnessMatchEnd(32);

	FitnessFunction * myFunction = new OneMaxFitness();
	ToStringFunction * myToString = new OneMaxToString();
	CrossoverOperation * myCrossover = new NPointCrossover(2);
	MutationOperation * myMutation = new UniformMutation(0.2);

	FitnessPropagator * myPropagator = new NonPropagator();

	int binaryDigits[] = {0,1};

	GeneNode ** baseGenes = (GeneNode**)malloc(sizeof(GeneNode*)*32);

	for (int i = 0; i < 32; i++) {
		baseGenes[i] = new LibraryNode<int>(binaryDigits, 2);
	}

	Individual * templateIndividual = new Individual(baseGenes, 32, myCrossover, myMutation, myFunction, myToString);

	PopulationNode * topLevelPool = new PopulationNode(64, templateIndividual, 100, 1, myGenerationModel, myEndCondition, myPropagator);

	delete(templateIndividual);
	
	topLevelPool->run(true);

	delete(topLevelPool);
	for (int i = 0; i < 32; i++) {
		delete(baseGenes[i]);
	}

	delete(myGenerationModel);
	delete(myMutation);
	delete(myCrossover);
	delete(myStrategy);
	delete(myEndCondition);
	delete(myFunction);
	delete(myToString);
	delete(myPropagator);

	free(baseGenes);
}

