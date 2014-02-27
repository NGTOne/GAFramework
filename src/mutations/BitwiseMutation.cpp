class BitwiseMutation : MutationOperation {
	private:

	protected:

	public:

	int[] mutate(int[] initialGenome, int[] largestPossibleValues) {
		int genomeLength = sizeof(initialGenome)/sizeof(int);
		int randomNumber;
		int newGenome[genomeLength];

		mt19937 generator(seed);
		uniform_int_distribution<int> mutationChanceDistribution(0, 10);

		for (int i = 0; i < genomeLength; i++) {
			randomNumber = mutationChanceDistribution(generator);

			if (randomNumber <= mutationChance*10) {
				//Due to the chosen representational model,
				//each gene in the genome might have a different
				//maximum value - hence, this is necessary
		                uniform_int_distribution<int> newValueDistribution(0, largestPossibleValues[i]);

				newGenome[i] = newValueDistribution(generator);
			} else {
				newGenome[i] = initialGenome[i];
			}
		}

		return newGenome;
	}
}
