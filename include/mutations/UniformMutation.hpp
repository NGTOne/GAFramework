#include "../nodes/EANode/MutationOperation.hpp"
#pragma once

/*
* The uniform mutation operator randomly decides whether or not to mutate
* a given allele along the genome, and then sets it to a random value from
* the allele's range.
*/

class UniformMutation : public MutationOperation {
	private:

	protected:
	virtual unsigned int getNewLocusValue(
		unsigned int currentValue,
		unsigned int largestPossibleValue
	);

	public:
	UniformMutation();
	UniformMutation(double mutationRate);
	UniformMutation(double mutationRate, unsigned seed);
};
