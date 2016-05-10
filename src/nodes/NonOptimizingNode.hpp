#include "core/NonEvolvingPopulationNode.hpp"
#include <sstream>
#include <iostream>

using namespace std;

NonEvolvingPopulationNode::NonEvolvingPopulationNode(
	int newPopulationSize,
	Individual * templateIndividual,
	int newMaxGenerations,
	int accelerationFactor,
	EndCondition * newCondition,
	FitnessPropagator * newPropagator
) : PopulationNode(
	newPopulationSize,
	templateIndividual,
	newMaxGenerations,
	accelerationFactor,
	NULL,
	newCondition,
	newPropagator
) {}

NonEvolvingPopulationNode::NonEvolvingPopulationNode(
	int newPopulationSize,
	Individual * templateIndividual,
	int newMaxGenerations,
	int accelerationFactor,
	EndCondition * newCondition,
	FitnessPropagator * newPropagator,
	int newSeed
) : PopulationNode(
	newPopulationSize,
	templateIndividual,
	newMaxGenerations,
	accelerationFactor,
	newSeed,
	NULL,
	newCondition,
	newPropagator
) {}

void NonEvolvingPopulationNode::nextGeneration() {
	if (currentGeneration < maxGenerations && optimumFound == false) {
		evaluateFitnesses();
		propagateFitnesses();
		currentGeneration++;
		checkEndCondition();
	}
}

string NonEvolvingPopulationNode::toString() {
	string returnString = "";
	stringstream ss;
	string populationString;

	ss << "Population size: " << populationSize << "\n";
	ss << populationStrings();

	if (readOnce == false) {
        	ss << "Seed: " << seed << "\n";
	}

	readOnce = true;

	returnString = ss.str();

	return returnString;
}
