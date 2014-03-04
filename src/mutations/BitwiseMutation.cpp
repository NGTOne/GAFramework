class BitwiseMutation : MutationOperation {
	private:

	protected:

	public:

	int[] mutate(int initialGenome[], int largestPossibleValues[]) {
		int genomeLength = sizeof(initialGenome)/sizeof(int);
		int randomNumber;
		int newGenome[genomeLength];

		mt19937 generator(seed);
		uniform_real_distribution mutationChanceDistribution(0, 1);

		for (int i = 0; i < genomeLength; i++) {
			randomNumber = mutationChanceDistribution(generator);

			if (randomNumber <= mutationChance) {
				//Due to the chosen representational model,
				//each gene in the genome might have a different
				//maximum value - hence, this is necessary
		                uniform_int_distribution newValueDistribution(0, largestPossibleValues[i]);

				newGenome[i] = newValueDistribution(generator);
			} else {
				newGenome[i] = initialGenome[i];
			}
		}

		return newGenome;
	}
}
