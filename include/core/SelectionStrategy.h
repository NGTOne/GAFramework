//This abstract class serves as a general base for all selection strategies,
//allowing any HierarchicalGenePool to use any strategy you might want
#include "Individual.h"

class SelectionStrategy {
	private:

	protected:
	unsigned seed;
	double crossoverRate;
	int numElites;

	public:

	SelectionStrategy(double newCrossoverRate, int newNumElites);

	SelectionStrategy(unsigned newSeed, double newCrossoverRate, int newNumElites);

	void sortPopulation(Individual initialPopulation[], int initialFitnesses[], int eliteLocations[], int populationSize);

	int getParent(int populationFitnesses[], int populationSize);

	Individual * breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize);
};
