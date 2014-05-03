#include "MutationOperation.h"
#pragma once

class UniformMutation : public MutationOperation {
	private:

	protected:

	public:

	UniformMutation();
	UniformMutation(double newMutationRate);
	UniformMutation(double newMutationRate, unsigned newSeed);

	Genome * mutate(Genome * initialGenome, int largestPossibleValues[]);

};
