#include "selections/TournamentSelection.hpp"
#include <random>
#include <sstream>
#include <algorithm>

using namespace std;

TournamentSelection::TournamentSelection(
	double crossoverRate
) : SelectionStrategy(
	crossoverRate,
	"Tournament"
) {
	init(DEFAULT_TOURNAMENT_SIZE);
}

TournamentSelection::TournamentSelection(
	double crossoverRate,
	unsigned int tournamentSize
) : SelectionStrategy(
	crossoverRate,
	"Tournament"
) {
	init(tournamentSize);
}

TournamentSelection::TournamentSelection(
	double crossoverRate,
	unsigned int tournamentSize,
	unsigned seed
) : SelectionStrategy(seed, crossoverRate, "Tournament") {
	init(tournamentSize);
}

void TournamentSelection::init(unsigned int tournamentSize) {
	this->tournamentSize = tournamentSize;
}

void TournamentSelection::sortByFitness(
	vector<int> indexes,
	vector<int> fitnesses
) {
	int tempIndex, tempFitness;
	for (int i = 0; i < indexes.size(); i++) {
		for (int k = 0; k < indexes.size(); k++) {
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

int TournamentSelection::getParent(
	vector<Genome*> population,
	vector<int> fitnesses
) {
	unsigned int populationSize = fitnesses.size();
	unsigned int tournamentSize = min(
		this->tournamentSize,
		populationSize
	);
	vector<int> tempFitnesses, indexes;
	int index;

        uniform_real_distribution<double> selectionDist(0,1);
	uniform_int_distribution<int> indexDist(0, fitnesses.size() - 1);

	for (int i = 0; i < tournamentSize; i++) {
		index = indexDist(this->generator);
		tempFitnesses.push_back(fitnesses[index]);
		indexes.push_back(index);
	}

	sortByFitness(indexes, tempFitnesses);

	for (int i = 0; i < tournamentSize; i++) {
		if (
			selectionDist(generator) < crossoverRate
			|| i == tournamentSize - 1
		) {
			return indexes[i];
		}
	}
}

string TournamentSelection::toString() {
	stringstream ss;

	ss << "Name: " << name
	<< "\nTournament size: " << tournamentSize
	<< "\nRandom seed: " << seed
	<< "\nCrossover Rate: " << crossoverRate
	<< "\n";

	return ss.str();
}
