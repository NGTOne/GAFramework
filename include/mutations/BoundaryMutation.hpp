#include "../nodes/EANode/MutationOperation.hpp"
#pragma once

/*
* The boundary mutation operator randomly decides whether or not to mutate
* a given allele along the genome, and then randomly sets it to either its
* maximum or minimum value.
*/

class BoundaryMutation : public MutationOperation {
	private:

	protected:
	virtual unsigned int getNewLocusValue(
		unsigned int currentValue,
		unsigned int largestPossibleValue
	);

	public:
	BoundaryMutation();
	BoundaryMutation(double mutationRate);
	BoundaryMutation(double mutationRate, unsigned int seed);
};
