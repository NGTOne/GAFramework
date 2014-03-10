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


	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize) {
		Individual mutantChildren[populationSize];
		Individual crossoverChildren[populationSize];
		Individual finalPopulation[populationSize];
		Individual overallPopulation[populationSize*3];
		int newPopulationFitnesses[populationSize*3];
		int eliteLocations[populationSize];
		int newEliteLocations[populationSize*3];

		Individual firstParent;
		Individual secondParent;
		Individual children[];

		int firstIndex;
		int secondIndex;

		for (int i = 0; i < populationSize; i++) {
			eliteLocations[i] = 0;
		}

		for (int i = 0; i < populationSize*3; i++) {
			newPopulationFitnesses[i] = 0;
			newEliteLocations[i] = 0;
		}

		//Each individual produces one mutant
		for (int = 0; i < populationSize; i++) {
			mutantChildren[i] = initialPopulation[i].mutationOperation();
		}

		//Each pair of individuals produces two children
		//We mess with the population size to prevent array size
		//overruns
		for (int i = 0; i < ((populationSize/2)*2); i+=2) {
			firstIndex = getParent(populationFitnesses, populationSize);
			secondIndex = getParent(populationFitnesses, populationSize);
			firstParent = initialPopulation[firstIndex];
        	        secondParent = initialPopulation[secondIndex];

                	children = firstParent.crossoverOperation(secondParent);

			crossoverChildren[i] = children[0];
			crossoverChildren[i+1] = children[1];
		}

		//Pick the elites - we can assume that the initial list has been sorted
		//during the last generation
		//If the number of elites is equal to or greater than the population size,
		//we just mark the entire population as elite and call it a day
		for (int i = 0; i < numElites && i < populationSize; i++) {
			eliteLocations[i] = 1;
		}


		//OK, now we have all the results of our breeding and mutation
		//Time to pick the ones that will move on to the next
		//generation
		//First, we lump them all together into one big population
		for (int i = 0; i < populationSize; i++) {
			overallPopulation[i] = originalPopulation[i];
			newPopulationFitnesses[i] = originalFitnesses[i];
			newEliteLocations[i] = eliteLocations[i];
			overallPopulation[i+populationSize] = mutantChildren[i];
			newPopulationFitnesses[i+populationSize] = mutantChildren[i].checkFitness();
			overallPopulation[i+(populationSize*2)] = crossoverChildren[i];
			newPopulationFitnesses[i+(populationSize*2)] = crossoverChildren[i].checkFitness();
		}

		//Now, of course, we sort them
		overallPopulation = sortPopulation(overallPopulation, newPopulationFitnesses, newEliteLocations, populationSize*3);

		
	}
}
