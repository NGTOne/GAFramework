//Abstract class for mutation operators. Lets us define any mutation operation we like.

class MutationOperation {
	private:

	protected:
	int nonRandomSeed;
        boolean overrideRandom = false;
	int mutationRate;

	public:

	MutationOperation(int newMutationRate) {
		mutationRate = newMutationRate;
	}

	MutationOperation(int newMutationRate, boolean randomStatus, int overriddenSeed) {
                mutationRate = newMutationRate;
		overrideRandom = randomStatus;
                nonRandomSeed = overriddenSeed;
        }

	int[] mutate(int initialGenome[]);
}
