#include "../core/FitnessPropagator.hpp"
#pragma once

/*
* The DownPropagator subclass of FitnessPropagator sends the current level's
* fitnesses down to the next level. This allows the higher-level individuals
* to define the fitness of their various sub-components.
*/

class DownPropagator : public FitnessPropagator {
	private:

	protected:

	public:
	void propagateFitnesses(Individual ** population, int populationSize);
};
