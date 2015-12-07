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
	uniform_int_distribution indexDistribution(0, populationSize-1);

	firstIndex = indexDistribution(generator);
	while (selectionDistribution(generator) > crossoverRate) {
		firstIndex = indexDistribution(generator);
	}

	secondIndex = indexDistribution(generator);
	while (selectionDistribution(generator) > crossoverRate) {
		secondIndex = indexDistribution(generator);
	}

	firstFitness = populationFitnesses[firstIndex];
	secondFitness = populationFitnesses[secondIndex];

	if (firstFitness >= secondFitness) {
		return firstIndex;
	} else {
		return secondIndex;
	}
}
