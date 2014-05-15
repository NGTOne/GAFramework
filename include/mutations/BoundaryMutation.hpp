#include "MutationOperation.hpp"
#pragma once

class BoundaryMutation : public MutationOperation {
	private:

	protected:

	public:

	BoundaryMutation();
	BoundaryMutation(double newMutationRate);
	BoundaryMutation(double newMutationRate, unsigned newSeed);

	Genome * mutate(Genome * initialGenome, int largestPossibleValues[]);

};
