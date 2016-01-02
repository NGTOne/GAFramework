#include "selections/TournamentSelection.hpp"
#include <random>
#include <chrono>

using namespace std;

TournamentSelection::TournamentSelection(double newCrossoverRate) : SelectionStrategy(chrono::system_clock::now().time_since_epoch().count(), newCrossoverRate, "Tournament") {
	init(2);
}

TournamentSelection::TournamentSelection(unsigned newSeed, double newCrossoverRate) : SelectionStrategy(newSeed, newCrossoverRate, "Tournament") {
	init(2);
}

TournamentSelection::TournamentSelection(
	double newCrossoverRate,
	int newTournamentSize
) : SelectionStrategy(
	chrono::system_clock::now().time_since_epoch().count(),
	newCrossoverRate,
	"Tournament"
) {
	init(newTournamentSize);
}

TournamentSelection::TournamentSelection(
	unsigned newSeed,
	double newCrossoverRate,
	int newTournamentSize
) : SelectionStrategy(newSeed, newCrossoverRate, "Tournament") {
	init(newTournamentSize);
}

void TournamentSelection::init(int newTournamentSize) {
	tournamentSize = newTournamentSize;
}

void TournamentSelection::sortByFitness(int indexes[], int fitnesses[]) {
	int tempIndex, tempFitness;
	for (int i = 0; i < tournamentSize; i++) {
		for (int k = i + 1; k < tournamentSize; k++) {
			if (fitnesses[k] > fitnesses[i]) {
				tempFitness = fitnesses[k];
				tempIndex = indexes[k];
				fitnesses[k] = fitnesses[i];
				indexes[k] = indexes[i];
				fitnesses[i] = tempFitness;
				indexes[i] = tempIndex;
			}
		}
	}
}

int TournamentSelection::getParent(int populationFitnesses[], int populationSize) {
	int fitnesses[tournamentSize];
	int indexes[tournamentSize];
	int index;

        uniform_real_distribution<double> selectionDistribution(0,1);
	uniform_int_distribution<int> indexDistribution(0, populationSize-1);

	for (int i = 0; i < tournamentSize; i++) {
		index = indexDistribution(generator);
		fitnesses[i] = populationFitnesses[index];
		indexes[i] = index;
	}

	sortByFitness(indexes, fitnesses);

	for (int i = 0; i < tournamentSize; i++) {
		if (selectionDistribution(generator) < crossoverRate || i == tournamentSize - 1) {
			return indexes[i];
		}
	}
}
