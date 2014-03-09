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

	Individual[] sortPopulation(Individual initialPopulation[], int initialFitnesses[], int populationSize) {
		//Since we're unlikely to be dealing with gigantic populations,
		//a simple sort that's O(n^2) or better and easy to implement
		//will suffice here. TODO: Make it more efficient
		Individual tempIndividual;
		int temp;

		for (int i = 0; i < populationSize; i++) {
			for (int k = 0; k < populationSize; k++) {
				if (initialFitnesses[i] > initialFitnesses[k]) {
					tempIndividual = initialPopulation[i];
					temp = initialFitnesses[i];

					initialPopulation[i] = initialPopulation[k];
					initialFitnesses[i] = initialFitnesses[k];

					initialPopulation[k] = tempIndividual;
					initialFitnesses[k] = temp;
				}
			}
		}

		return initialPopulation;
	}

	int getParent(int populationFitnesses[], int populationSize);
	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize);
}
