#include "../core/FitnessPropagator.hpp"
#pragma once

class DownPropagator : public FitnessPropagator {
	private:

	protected:

	public:
	void propagateFitnesses(Individual ** population, int populationSize);
};
