#include "MutationOperation.h"
#pragma once

class UniformMutation : public MutationOperation {
	private:

	protected:

	public:

	UniformMutation();
	UniformMutation(double newMutationRate);
	UniformMutation(double newMutationRate, unsigned newSeed);

	int * mutate(int initialGenome[], int largestPossibleValues[], int genomeLength);

};
