#include "../core/MutationOperation.hpp"
#pragma once

//Boundary mutation is a bitwise-type of mutation, which randomly determines
//whether or not each gene will mutate. If a gene is selected for mutation,
//it is set randomly to either its lowest or highest possible value.
class BoundaryMutation : public MutationOperation {
	private:

	protected:

	public:

	BoundaryMutation();
	BoundaryMutation(double newMutationRate);
	BoundaryMutation(double newMutationRate, unsigned newSeed);

	Genome * mutate(Genome * initialGenome, int largestPossibleValues[]);

};
