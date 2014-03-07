class TournamentSelection : SelectionStrategy {
	private:

	protected:

	public:

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


	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize) {
		Individual mutantChildren[populationSize];
		Individual crossoverChildren[populationSize];
		Individual finalPopulation[populationSize];

		Individual firstParent;
		Individual secondParent;
		Individual children[];

		int firstIndex;
		int secondIndex;

		//Each individual produces one mutant
		for (int = 0; i < populationSize; i++) {
			mutantChildren[i] = initialPopulation[i].mutationOperation();
		}

		//Each pair of individuals produces two children
		//We mess with the population size to prevent array size
		//overruns
		for (int i = 0; i < ((populationSize/2)*2)+1; i+=2) {
			firstIndex = getParent(populationFitnesses, populationSize);
			secondIndex = getParent(populationFitnesses, populationSize);
			firstParent = initialPopulation[firstIndex];
        	        secondParent = initialPopulation[secondIndex];

                	children = firstParent.crossoverOperation(secondParent);

			crossoverChildren[i] = children[0];
			crossoverChildren[i+1] = children[1];
		}
		
	}
}
