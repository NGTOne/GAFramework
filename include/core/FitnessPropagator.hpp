#pragma once
#include "Individual.hpp"

/*
* This abstract class allows us to propagate fitnesses down the hierarchical
* GA tree as we desire, in order to create structures that "inherit" the
* fitnesses of their parent nodes. This opens many new avenues for the
* structure of a hierchical GA.
*/

class FitnessPropagator {
	private:

	protected:

	public:
	virtual void propagateFitnesses(
		Individual ** population,
		int populationSize
	)=0;
};
