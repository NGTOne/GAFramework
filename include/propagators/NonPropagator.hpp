#include "../core/FitnessPropagator.hpp"
#pragma once

//This subclass of FitnessPropagator does nothing at all - it serves merely
//to provide a way NOT to propagate fitness through the tree.
class NonPropagator : public FitnessPropagator {
	private:

	protected:

	public:
	void propagateFitnesses(Individual ** population, int populationSize);
};
