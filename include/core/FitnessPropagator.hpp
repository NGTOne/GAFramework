#pragma once
#include "Individual.hpp"

//By providing ways to allow sub-components to inherit the fitness of their
//parents in the tree, we open the door to all sorts of new structures for
//hierarchical GAs, and new areas to explore.
//This abstract class allows us to push fitnesses around the HGA tree as
//we please.
class FitnessPropagator {
	private:

	protected:

	public:
	virtual void propagateFitnesses(Individual ** population, int populationSize)=0;
};
