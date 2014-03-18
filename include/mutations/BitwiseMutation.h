#include "MutationOperation.h"
#pragma once

class BitwiseMutation : public MutationOperation {
	private:

	protected:

	public:

	BitwiseMutation();
	BitwiseMutation(double newMutationRate);
	BitwiseMutation(double newMutationRate, unsigned newSeed);

	int * mutate(int initialGenome[], int largestPossibleValues[], int genomeLength);

};
