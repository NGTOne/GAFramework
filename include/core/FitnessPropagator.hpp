#pragma once
#include "Individual.hpp"

class FitnessPropagator {
	private:

	protected:

	public:
	virtual void propagateFitnesses(Individual ** population, int populationSize)=0;
};
