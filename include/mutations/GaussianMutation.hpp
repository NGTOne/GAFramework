#include "../core/MutationOperation.hpp"
#pragma once

/*
* Gaussian mutation changes the value of the allele by randomly generating
* a number on the normal distribution and adding it to the allele's value
*/

class GaussianMutation : public MutationOperation {
	private:

	protected:

	public:
	GaussianMutation();
	GaussianMutation(double mutationRate);
	GaussianMutation(double mutationRate, unsigned seed);

	Genome * mutate(Genome * initialGenome, int largestPossibleValues[]);
};
