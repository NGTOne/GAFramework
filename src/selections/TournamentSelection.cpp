#include "selections/TournamentSelection.hpp"
#include <random>
#include <chrono>

using namespace std;

TournamentSelection::TournamentSelection(double newCrossoverRate) : SelectionStrategy(chrono::system_clock::now().time_since_epoch().count(), newCrossoverRate, "Tournament") {}

TournamentSelection::TournamentSelection(unsigned newSeed, double newCrossoverRate) : SelectionStrategy(newSeed, newCrossoverRate, "Tournament") {}

//Picks two random indices, gets their fitnesses, then compares them
//and returns the index with the higher fitness
int TournamentSelection::getParent(int populationFitnesses[], int populationSize) {
	int firstFitness = 0;
	int secondFitness = 0;
	int firstIndex;
	int secondIndex;
	bool pickedTwo = false;

        uniform_real_distribution<double> selectionDistribution(0,1);

	while (pickedTwo == false) {
		for (int k = 0; k < populationSize; k++) {
                        secondFitness = 0;

			if (selectionDistribution(generator) < crossoverRate) {
                                firstFitness = populationFitnesses[k];
				firstIndex = k;

				for (int c = 0; c < populationSize; c++) {
					if (selectionDistribution(generator) < crossoverRate) {
						secondFitness = populationFitnesses[c];
						secondIndex = c;

                        	                c = populationSize + 1;
						pickedTwo = true;
                	                }
				}

				if (pickedTwo == true) {
                                	k = populationSize + 1;
                        	}
                	}
		}
	}

	if (firstFitness >= secondFitness) {
		return firstIndex;
	} else {
		return secondIndex;
	}
}
