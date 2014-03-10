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
	int numElites;

	public:

	SelectionStrategy(double newCrossoverRate, int newNumElites) : crossoverRate(newCrossoverRate), numElites(newNumElites) {
		seed = chrono::system_clock::now().time_since_epoch().count();
	}

	SelectionStrategy(unsigned newSeed, double newCrossoverRate, int newNumElites) : seed(newSeed), crossoverRate(newCrossoverRate), numElites(newNumElites) {}

	Individual[] sortPopulation(Individual initialPopulation[], int initialFitnesses[], int eliteLocations[], int populationSize) {
		//Since we're unlikely to be dealing with gigantic populations,
		//a simple sort that's O(n^2) or better and easy to implement
		//will suffice here.
		//TODO: Make it more efficient
		Individual tempIndividual;
		int temp;
		int tempBool;

		for (int i = 0; i < populationSize; i++) {
			for (int k = 0; k < populationSize; k++) {
				if (initialFitnesses[i] > initialFitnesses[k]) {
					tempIndividual = initialPopulation[i];
					temp = initialFitnesses[i];
					tempBool = eliteLocations[i];

					initialPopulation[i] = initialPopulation[k];
					initialFitnesses[i] = initialFitnesses[k];
					eliteLocations[i] = eliteLocations[k];

					initialPopulation[k] = tempIndividual;
					initialFitnesses[k] = temp;
					eliteLocations[k] = tempBool;
				}
			}
		}

		return initialPopulation;
	}

	int getParent(int populationFitnesses[], int populationSize);
	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize);
}
