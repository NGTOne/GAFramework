#include "../core/FitnessPropagator.hpp"
#pragma once

class NonPropagator : public FitnessPropagator {
	private:

	protected:

	public:
	void propagateFitnesses(Individual ** population, int populationSize);
};
