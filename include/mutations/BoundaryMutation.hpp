#include "../core/MutationOperation.hpp"
#pragma once

/*
* The boundary mutation operator randomly decides whether or not to mutate
* a given allele along the genome, and then randomly sets it to either its
* maximum or minimum value.
*/

class BoundaryMutation : public MutationOperation {
	private:

	protected:

	public:

	BoundaryMutation();
	BoundaryMutation(double newMutationRate);
	BoundaryMutation(double newMutationRate, unsigned newSeed);

	Genome * mutate(Genome * initialGenome, int largestPossibleValues[]);

};
