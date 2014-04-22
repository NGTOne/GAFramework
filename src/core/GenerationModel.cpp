//This abstract class serves as a general base for all generation models,
//allowing any HierarchicalGenePool to use any model you might want

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "SelectionStrategy.h"
#include "GenerationModel.h"

using namespace std;

GenerationModel::GenerationModel(int newNumElites, SelectionStrategy * newStrategy) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(newNumElites, seed, newStrategy);
}

GenerationModel::GenerationModel(unsigned newSeed, int newNumElites, SelectionStrategy * newStrategy) {
	init(newNumElites, newSeed, newStrategy);
}

void GenerationModel::init(int newNumElites, unsigned newSeed, SelectionStrategy * newStrategy) {
	seed = newSeed;
	numElites = newNumElites;
	mt19937 newGenerator(seed);
	generator = newGenerator;
	myStrategy = newStrategy;
}

void GenerationModel::sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize) {
	//Since we're unlikely to be dealing with gigantic populations, a
	//simple sort that's O(n^2) or better and easy to implement will
	//suffice here.
	//TODO: Make it more efficient
	Individual * tempIndividual;
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
}

int GenerationModel::getParent(int * populationFitnesses, int populationSize) {
	return myStrategy->getParent(populationFitnesses, populationSize);
}

string GenerationModel::toString() {
	string returnString = "";
        stringstream ss;
	
	ss << "Random seed: " << seed << "\nNumber of elites: " << numElites << "\nSelection Strategy: ";

	ss << myStrategy->toString();

	ss << "\n";

	returnString = ss.str();

	return returnString;
}
