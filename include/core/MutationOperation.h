//Abstract class for mutation operators. Lets us define any mutation operation we like.
#pragma once

class MutationOperation {
	private:

	protected:
	unsigned seed;
        int mutationRate;

	public:

	MutationOperation();
	MutationOperation(int newMutationRate);
	MutationOperation(int newMutationRate, unsigned newSeed);

	virtual int * mutate(int initialGenome[], int largestPossibleValues[], int genomeLength)=0;
};
