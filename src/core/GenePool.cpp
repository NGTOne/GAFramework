#include <cstdlib>
#include <random>
#include <chrono>

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
	unsigned seed;

	public:
	int chooseRandomMember();
	void runGenerations();
	int getPopulationSize();
	void * getIndex(int index);
	Individual getFittestMember();

	GenePool() {
		seed = chrono::system_clock::now().time_since_epoch().count();
	}

	GenePool(unsigned overriddenSeed) : seed(overriddenSeed) {}

	int getPopulationSize() {
		return populationSize;
	}

	int chooseRandomMember() {
		mt19937 generator(seed);
		uniform_int_distribution selectionDistribution(0, populationSize-1);

		int randomMember = selectionDistribution(generator);

		return randomMember;
	}
}
