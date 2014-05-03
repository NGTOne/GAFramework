#include "MutationOperation.h"
#pragma once

class BoundaryMutation : public MutationOperation {
	private:

	protected:

	public:

	BoundaryMutation();
	BoundaryMutation(double newMutationRate);
	BoundaryMutation(double newMutationRate, unsigned newSeed);

	Genome * mutate(int initialGenome[], int largestPossibleValues[], int genomeLength);

};
