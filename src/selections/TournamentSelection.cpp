class TournamentSelection : SelectionStrategy {
	private:

	protected:

	public:

	//Picks two random indices, gets their fitnesses, then compares them
	//and returns the index with the higher fitness
	int getParent(int populationFitnesses[], int populationSize) {
		int firstFitness = 0;
		int secondFitness = 0;
		int firstIndex;
		int secondIndex;

                mt19937 generator(seed);
                uniform_real_distribution selectionDistribution(0,1);

		for (int k = 0; k < populationSize; k++) {
                        secondFitness = 0;

                        if (selectionDistribution(generator) < crossoverRate) {
                                firstFitness = fitnesses[k];
				firstIndex = k;


                                for (int c = 0; c < populationSize; c++) {
                                        if (selectionDistribution(generator) < crossoverRate) {
                                                secondFitness = fitnesses[c];
						secondIndex = c;

                                        	c = populationSize + 1;
                                	}
                                }

                                if (c == populationSize + 1) {
                                	k = populationSize + 1;
                        	}
                	}
		}

		if (firstFitness >= secondFitness) {
			return firstIndex;
		} else {
			return secondIndex;
		}

	}
}
