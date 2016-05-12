#include "../nodes/EANode/MutationOperation.hpp"
#pragma once

/*
* Gaussian mutation changes the value of the allele by randomly generating
* a number on the normal distribution and adding it to the allele's value
*/

class GaussianMutation : public MutationOperation {
	private:

	protected:
	bool reflection;

	virtual int getNewLocusValue(
		int currentValue,
		int largestPossibleValue
	);

	void init(bool reflection);

	public:
	GaussianMutation();
	GaussianMutation(bool reflection);
	GaussianMutation(double mutationRate);
	GaussianMutation(double mutationRate, bool reflection);
	GaussianMutation(double mutationRate, unsigned seed);
	GaussianMutation(double mutationRate, bool reflection, unsigned seed);
};
