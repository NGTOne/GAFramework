//This abstract class serves as a general base for all selection strategies,
//allowing any HierarchicalGenePool to use any strategy you might want

class SelectionStrategy {
	private:

	protected:
	boolean overrideRandom = false;
	int nonRandomSeed;

	public:
	
	SelectionStrategy() {};

	SelectionStrategy(boolean randomStatus, int overriddenSeed) {
		overrideRandom = randomStatus;
		nonRandomSeed = overriddenSeed;
	}

	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize);
}
