#include "../core/FitnessPropagator.hpp"
#pragma once

/*
* The ApportioningPropagator subclass of FitnessPropagator is meant to allow
* Individuals to assign "credit" to their components - this means it has to be
* extended in an appropriate way
*/

class ApportioningPropagator : public FitnessPropagator {
	private:

	protected:
	// Gets the number of Individuals in the population that use the target
	int getIndividualCount(Individual ** population, int populationSize, Individual * target);
	// Gets the number of uses of the target (can be more than the number
	// of Individuals that use it)
	// Returns an array, so we know which Individuals use it how many times
	int * getUseCount(Individual ** population, int populationSize, Individual * target);

	virtual int getAssignableFitness(Individual ** population, int populationSize, Individual * target)=0;

	// Acts as a wrapper around getFitnessContribution, to allow us to do
	// things that the user shouldn't need to worry about
	int getFitnessValue(Individual * user, Individual * used);
	virtual int getFitnessContribution(Individual * user, Individual * used)=0;

	public:
	void propagateFitnesses(Individual ** population, int populationSize);
};
