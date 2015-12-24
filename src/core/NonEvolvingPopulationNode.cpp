#include "core/NonEvolvingPopulationNode.hpp"

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
		myPopulation[0]->runHierarchicalGenerations();
		evaluateFitnesses();
		propagateFitnesses();
		currentGeneration++;
		checkEndCondition();
	}
}
