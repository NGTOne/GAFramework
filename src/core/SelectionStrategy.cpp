//This abstract class serves as a general base for all selection strategies,
//allowing any HierarchicalGenePool to use any strategy you might want

#include <random>
#include <chrono>
using namespace std;

class SelectionStrategy {
	private:

	protected:
	unsigned seed;
	double crossoverRate;

	public:

	SelectionStrategy(double newCrossoverRate) : crossoverRate(newCrossoverRate) {
		seed = chrono::system_clock::now().time_since_epoch().count();
	}

	SelectionStrategy(unsigned newSeed, double newCrossoverRate) : seed(newSeed), crossoverRate(newCrossoverRate) {}

	int getParent(int populationFitnesses[], int populationSize);
	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize);
}
