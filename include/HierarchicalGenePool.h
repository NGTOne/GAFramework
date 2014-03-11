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
	HierarchicalGenePool(int populationSize, Individual templateIndividual, int myMaxGenerations, int numIterations = 1);

	//If we do know the optimum
	HierarchicalGenePool(int populationSize, Individual templateIndividual, int maxGenerations, int numIterations = 1, int[] optimalGenome);

	//Evaluates the fitnesses of the population of this particular
	//GenePool - basically a convenience thing
	void evaluateFitnesses();

	//Evaluates the fitnesses of a given population of individuals
	//Doesn't care what their genetic makeup is - uses their fitness
	//functions
	int[] evaluateFitnesses(Individual[] populationToEval, int populationToEvalSize);

	//When we need a specific individual
	void * getIndex(int index);

	//Run one generation
	void nextGeneration();

	//For HGAs - if we want to run multiple generations of a lower-level
	//gene pool for every one of a higher-level one, this is how
	//Basically a loop wrapped around nextGeneration()
	void runGenerations();

	Individual[] sortPopulation(Individual initialPopulation[], int initialFitnesses[], int populationSize);

};
