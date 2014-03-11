//This is a dual-purpose class for gene pools - it serves as a "base"
//GA, and also as a gene pool for individuals in hierarchical GAs
//Since these functions are, by and large, very similar, they can be
//combined together into one class
class HierarchicalGenePool : public GenePool {
	private:

	protected:
	Individual myPopulation[];

	int populationFitnesses[];

	int maxGenerations;
	int currentGeneration = 0;

	//In case we already know the optimum - needs to be specified for
	//every level of the hierarchy in an HGA, or it effectively becomes
	//meaningless
	boolean knownOptimum;
	int[] optimumGenome;
	int optimumFitness;
	double epsilon;
	boolean optimumFound = false;

	//Specifies how many generations should pass by "silently"
	//every time nextGeneration() is called - might be a useful parameter
	//for HGAs (to accelerate growth at the lower levels)
	int numIterationsPerGeneration;

	SelectionStrategy myStrategy;

	public:

	void evaluateFitnesses();
	void nextGeneration();
	Individual getIndex(int index);
	Individual[] sortPopulation(Individual initialPopulation[], int initialFitnesses[], int populationSize);
	

	//If we don't know the optimum
	HierarchicalGenePool(int populationSize, Individual templateIndividual, int myMaxGenerations, int numIterations = 1) {
		myPopulation = new Individual[populationSize];

		for (int i = 0; i < populationSize; i++) {
			myPopulation[i] = templateIndividual.makeRandomCopy();
		}

		knownOptimum = false;
		maxGenerations = myMaxGenerations;
		numIterationsPerGeneration = numIterations;

		evaluateFitnesses();

		sortPopulation(myPopulation, populationFitnesses, populationSize);
	}

	//If we do know the optimum
	HierarchicalGenePool(int populationSize, Individual templateIndividual, int maxGenerations, int numIterations = 1, int[] optimalGenome) {
		myPopulation = new Individual[populationSize];

                for (int i = 0; i < populationSize; i++) {
                        myPopulation[i] = templateIndividual.makeRandomCopy();
                }

                knownOptimum = true;
                maxGenerations = myMaxGenerations;
                numIterationsPerGeneration = numIterations;

		optimum = optimalGenome;

		Individual optimumIndividual = templateIndividual.makeSpecifiedCopy(optimalGenome);

		optimumFitness = optimumIndividual.checkFitness();

		evaluateFitnesses();

		sortPopulation(myPopulation, populationFitnesses, populationSize);
	}

	//Evaluates the fitnesses of the population of this particular
	//GenePool - basically a convenience thing
	void evaluateFitnesses() {
		for (int i = 0; i < populationSize; i++) {
			populationFitnesses[i] = myPopulation[i].checkFitness();
		}
	}

	//Evaluates the fitnesses of a given population of individuals
	//Doesn't care what their genetic makeup is - uses their fitness
	//functions
	int[] evaluateFitnesses(Individual[] populationToEval, int populationToEvalSize) {
		int populationToEvalFitnesses[] = new int[populationToEvalSize];

		for (int i = 0; i < populationToEvalSize; i++) {
			populationToEvalFitnesses[i] = populationToEval[i].checkFitness();
		}

		return populationToEvalFitnesses;
	}

	//When we need a specific individual
	void * getIndex(int index) {
		return (void *)myPopulation[index];
	}

	//Run one generation
	void nextGeneration() {
		Individual newPopulation[];

		if (currentGeneration < maxGenerations && (knownOptimum == false || (optimumFound != true && knownOptimum == true))) {
			newPopulation = myStrategy.breedMutateSelect(myPopulation, populationFitnesses, populationSize);

	                currentGeneration += 1;

			if (knownOptimum == true) {
                        	for (int i = 0; i < populationSize && optimumFound == false; i++) {
                                	//TODO: make this more approximate
                                	if (populationFitnesses[i] == optimumFitness) {
                                        	optimumFound = true;
                                	}
                        	}
			}
			//The new generation replaces the old
			myPopulation = newPopulation;
		}
	}

	//For HGAs - if we want to run multiple generations of a lower-level
	//gene pool for every one of a higher-level one, this is how
	//Basically a loop wrapped around nextGeneration()
	void runGenerations() {
		int target = numGenerations + numIterationsPerGeneration;

		for (int i = numGenerations; i <= target && i <= maxGenerations && optimumFound == false; i++) {
			nextGeneration();
		}
	}

	Individual[] sortPopulation(Individual initialPopulation[], int initialFitnesses[], int populationSize) {
		//TODO: Make more efficient
		Individual tempIndividual;
		int temp;

		for (int i = 0; i < populationSize; i++) {
			for (int k = 0; k < populationSize; k++) {
				if (initialFitnesses[k] > initialFitnesses[i]) {
					tempIndividual = initialPopulation[i];
					temp = initialFitnesses[i];

					initialPopulation[i] = initialPopulation[k];
					initialFitnesses[i] = initialFitnesses[k];

					initialPopulation[k] = tempIndividual;
					initialFitnesses[i] = temp;
				}
			}
		}
	}

	return initialPopulation;
}
