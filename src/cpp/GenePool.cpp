#include <cstdlib>

//This is a base class for both hierarchical and non-hierarchical gene pools
//For hierarchical pools, each individual is an instance of the Individual
//class. For non-hierarchical pools, each "individual" is some literal, for
//instance the letters A-Z or the binary digits 0,1.
//A "standard" GA would be implemented like this:
//HierarchicalPool -> Individual -> (NonHierarchicalPool, NonHierarchicalPool)
class GenePool {
	private:

	protected:
	int populationSize;	
	int nonRandomSeed;
	boolean overrideRandom = false;

	public:
	int chooseRandomMember();
	void runGenerations();
	int getPopulationSize();
	void * getIndex(int index);

	GenePool() {};

	GenePool(boolean randomStatus, int overriddenSeed) {
		overrideRandom = randomStatus;
		nonRandomSeed = overriddenSeed;
	}

	int getPopulationSize() {
		return populationSize;
	}

	int chooseRandomMember() {
		//TODO: MAKE THIS RANDOM
		return populationSize - (populationSize/2);
	}
}
