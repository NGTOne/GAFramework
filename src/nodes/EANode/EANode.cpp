//This is a dual-purpose class for gene pools - it serves as a "base"
//GA, and also as a gene pool for individuals in hierarchical GAs
//Since these functions are, by and large, very similar, they can be
//combined together into one class

#include "core/PopulationNode.hpp"
#include <sstream>
#include <iostream>

using namespace std;

//If we don't know the optimum
PopulationNode::PopulationNode(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, EvolutionarySystem * newModel, EndCondition * newCondition, FitnessPropagator * newPropagator) : GeneNode() {
	init(newPopulationSize, templateIndividual, myMaxGenerations, numIterations, newModel, newCondition, newPropagator);
}

//Unknown optimum, overridden seed
PopulationNode::PopulationNode(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, int newSeed, EvolutionarySystem * newModel, EndCondition * newCondition, FitnessPropagator * newPropagator) : GeneNode(newSeed) {
	init(newPopulationSize, templateIndividual, myMaxGenerations, numIterations, newModel, newCondition, newPropagator);
}

PopulationNode::~PopulationNode() {
	for (int i = 0; i < populationSize; i++) {
		delete(myPopulation[i]);
	}

	free(myPopulation);
	free(populationFitnesses);
}

void PopulationNode::init(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, EvolutionarySystem * newModel, EndCondition * newCondition, FitnessPropagator * newPropagator) {
	myPopulation = (Individual**)malloc(sizeof(Individual*)*newPopulationSize);

	populationFitnesses = (int*)malloc(sizeof(int)*newPopulationSize);

	populationSize = newPopulationSize;
        currentGeneration = 0;
	readOnce = false;

	maxGenerations = myMaxGenerations;
	numIterationsPerGeneration = numIterations;
	myModel = newModel;
	myCondition = newCondition;
	myPropagator = newPropagator;

        for (int i = 0; i < populationSize; i++) {
                myPopulation[i] = templateIndividual->makeRandomCopy();
        }

        optimumFound = false;

        evaluateFitnesses();
}

//Evaluates the fitnesses of the population of this particular GeneNode
//Basically a convenience thing
void PopulationNode::evaluateFitnesses() {
	for (int i = 0; i < populationSize; i++) {
		populationFitnesses[i] = myPopulation[i]->checkFitness();
	}
}

Individual ** PopulationNode::newPopulation() {
	return myModel->breedMutateSelect(
		myPopulation,
		populationFitnesses,
		populationSize
	);
}

//Evaluates the fitnesses of a given population of individuals
//Doesn't care what their genetic makeup is - uses their fitness functions
int * PopulationNode::evaluateFitnesses(Individual ** populationToEval, int populationToEvalSize) {
	int * populationToEvalFitnesses = (int*)malloc(sizeof(int)*populationToEvalSize);

	for (int i = 0; i < populationToEvalSize; i++) {
		populationToEvalFitnesses[i] = populationToEval[i]->checkFitness();
	}

	return populationToEvalFitnesses;
}

//When we need a specific individual
void * PopulationNode::getIndex(int index) {
	void * returnValue;

	returnValue = (void*)myPopulation[index];

	return returnValue;
}

//Run one generation
void PopulationNode::nextGeneration() {
	Individual ** nextPopulation;

	if (currentGeneration < maxGenerations && optimumFound == false) {
		//Re-evaluate the fitnesses to take the lower GeneNodes
		//running their generations into account
		evaluateFitnesses();

		//We propagate after evaluating because we want the lower
		//levels that DON'T get propagated to (if they exist) to
		//act like normal
		propagateFitnesses();

		nextPopulation = newPopulation();

                currentGeneration += 1;

		//The new generation replaces the old
		for (int i = 0; i < populationSize; i++) {
			delete(myPopulation[i]);
			myPopulation[i] = nextPopulation[i]->deepCopy();
			delete(nextPopulation[i]);
		}

		free(nextPopulation);
		evaluateFitnesses();
		checkEndCondition();
	}

	// So we're still fitness-checking after we're done evolving
	if (optimumFound) evaluateFitnesses();
}

void PopulationNode::checkEndCondition() {
	if (myCondition != NULL) {
		optimumFound = myCondition->checkCondition(myPopulation, populationSize);
	}
}

void PopulationNode::propagateFitnesses() {
	if (myPropagator != NULL) {
		myPropagator->propagateFitnesses(myPopulation, populationSize);
	}
}

//For HGAs - if we want to run multiple generations of a lower-level gene pool
//for every one of a higher-level one, this is how
//Basically a loop wrapped around nextGeneration()
void PopulationNode::runGenerations() {
	int target = currentGeneration + numIterationsPerGeneration;

	for (int i = currentGeneration; i < target && i < maxGenerations && optimumFound == false; i++) {
		nextGeneration();
	}
}

void PopulationNode::sortPopulation() {
	myModel->sortPopulation(myPopulation, populationFitnesses, populationSize);
}

void PopulationNode::setFitnessAtIndex(int index, int newFitness) {
	myPopulation[index]->setFitness(newFitness);
}

void PopulationNode::insert(int index, Individual * target) {
	delete(myPopulation[index]);
	myPopulation[index] = target;
	populationFitnesses[index] = target->checkFitness();
}

int PopulationNode::getFitnessAtIndex(int index) {
	return populationFitnesses[index];
}

bool PopulationNode::done() {
	return currentGeneration >= maxGenerations - 1 || optimumFound;
}

string PopulationNode::populationStrings() {
	string returnString = "";
	stringstream ss;
	string populationString;
	
	for (int i = 0; i < populationSize; i++) {
		if (readOnce == false) {
			populationString = myPopulation[i]->toString();
		} else {
			populationString = myPopulation[i]->toGenomeString();
		}

		ss << "Member " << i << ": " << populationString << " Fitness: " << populationFitnesses[i] << "\n";
	}

	return ss.str();
}

string PopulationNode::toString() {
	string returnString = "";
	stringstream ss;
	string populationString;

	ss << "Population size: " << populationSize << "\n";
	ss << populationStrings();

	if (readOnce == false) {
        	ss << "Seed: " << seed << "\n";
	        ss << "Selection Info:\n" << myModel->toString();
	}

	readOnce = true;

	returnString = ss.str();

	return returnString;
}
