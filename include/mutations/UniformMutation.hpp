#include "../core/MutationOperation.hpp"
#pragma once

/*
* The uniform mutation operator randomly decides whether or not to mutate
* a given allele along the genome, and then sets it to a random value from
* the allele's range.
*/

class UniformMutation : public MutationOperation {
	private:

	protected:

	public:

	UniformMutation();
	UniformMutation(double newMutationRate);
	UniformMutation(double newMutationRate, unsigned newSeed);

	Genome * mutate(Genome * initialGenome, int largestPossibleValues[]);

};
