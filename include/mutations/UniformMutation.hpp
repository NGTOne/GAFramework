#include "../core/MutationOperation.hpp"
#pragma once

//Uniform mutation is a bitwise type of mutation, which randomly determines
//whether or not each gene will mutate. If a gene is selected for mutation,
//its new value is chosen randomly and uniformly from its list of possible
//values.
class UniformMutation : public MutationOperation {
	private:

	protected:

	public:

	UniformMutation();
	UniformMutation(double newMutationRate);
	UniformMutation(double newMutationRate, unsigned newSeed);

	Genome * mutate(Genome * initialGenome, int largestPossibleValues[]);

};
