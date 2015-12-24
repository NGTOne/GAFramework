#include "PopulationNode.hpp"
#pragma once

class NonEvolvingPopulationNode : public PopulationNode {
	private:

	protected:
	void init(int newPopulationSize, Individual * templateIndividual, int newMaxGenerations, int accelerationFactor, EndCondition * newCondition, FitnessPropagator * newPropagator);

	public:
	NonEvolvingPopulationNode(int newPopulationSize, Individual * templateIndividual, int newMaxGenerations, int accelerationFactor, EndCondition * newCondition, FitnessPropagator * newPropagator);
	NonEvolvingPopulationNode(int newPopulationSize, Individual * templateIndividual, int newMaxGenerations, int accelerationFactor, EndCondition * newCondition, FitnessPropagator * newPropagator, int newSeed);

	void nextGeneration();
}