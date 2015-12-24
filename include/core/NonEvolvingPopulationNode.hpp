#include "PopulationNode.hpp"
#pragma once

class NonEvolvingPopulationNode : public PopulationNode {
	private:

	protected:

	public:
	NonEvolvingPopulationNode(
		int newPopulationSize,
		Individual * templateIndividual,
		int newMaxGenerations,
		int accelerationFactor,
		EndCondition * newCondition,
		FitnessPropagator * newPropagator
	);

	NonEvolvingPopulationNode(
		int newPopulationSize,
		Individual * templateIndividual,
		int newMaxGenerations,
		int accelerationFactor,
		EndCondition * newCondition,
		FitnessPropagator * newPropagator,
		int newSeed
	);

	void nextGeneration();
	std::string toString();
};
