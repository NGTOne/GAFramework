#include "../core/FitnessPropagator.hpp"
#pragma once

//This subclass of FitnessPropagator does exactly what it says on the tin
//It sends the current level's fitnesses down to the next level, and calls
//that level's propagator (to continue the cycle)
class DownPropagator : public FitnessPropagator {
	private:

	protected:

	public:
	void propagateFitnesses(Individual ** population, int populationSize);
};
