class TournamentSelection : SelectionStrategy {
	private:

	protected:

	public:
	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize) {
		Individual mutantChildren[populationSize];
		Individual crossoverChildren[populationSize];
		Individual finalPopulation[populationSize];

		Individual firstParent;
		Individual secondParent;

		int firstFitness;
		int secondFitness;

		int firstIndex;
		int secondIndex;

		mt19937 generator(seed);
		uniform_real_distribution selectionDistribution(0,1)

		for (int = 0; i < populationSize; i++) {
			//TODO: Some mutation stuff here
		}

		for (int i = 0; i < populationSize; i++) {
			secondFitness = 0;

			if (selectionDistribution(generator) < crossoverRate) {
				firstFitness = fitnesses[i];

				for (int k = 0; k < populationSize; k++) {
					if (selectionDistribution(generator) < crossoverRate) {
						secondFitness = fitnesses[k];

						//TODO: Selection stuff
					}
				}


			}
		}
	}
}
