//This is an abstract class for crossover operations. Lets us define any 
//crossover we like, and use it for a given Individual.

class CrossoverOperation {
	private:

	protected:
	int nonRandomSeed;
        boolean overrideRandom = false;
        int crossoverRate;

	public:

	CrossoverOperation(int newCrossoverRate) {
                crossoverRate = newCrossoverRate;
        }

        CrossoverOperation(int newCrossoverRate, boolean randomStatus, int overriddenSeed) {
                crossoverRate = newCrossoverRate;
                overrideRandom = randomStatus;
                nonRandomSeed = overriddenSeed;
        }	

	int[] crossOver(int genomeOne[], int genomeTwo[]);
}
