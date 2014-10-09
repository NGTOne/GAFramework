#include "../core/FitnessPropagator.hpp"
#pragma once

/*
* This subclass of FitnessPropagator simply does nothing - it does NOT
* propagate fitnesses anywhere, and allows us to stop propagations from going
* further.
*/

class NonPropagator : public FitnessPropagator {
	private:

	protected:

	public:
	void propagateFitnesses(Individual ** population, int populationSize);
};
