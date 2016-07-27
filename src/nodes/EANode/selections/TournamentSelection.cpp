#include "nodes/EANode/selections/TournamentSelection.hpp"
#include "core/HierRNG.hpp"
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
	this->init(DEFAULT_TOURNAMENT_SIZE);
}

TournamentSelection::TournamentSelection(
	double crossoverRate,
	unsigned int tournamentSize
) : SelectionStrategy(
	crossoverRate,
	"Tournament"
) {
	this->init(tournamentSize);
}

void TournamentSelection::init(unsigned int tournamentSize) {
	this->tournamentSize = tournamentSize;
}

void TournamentSelection::sortByFitness(
	vector<unsigned int> & indexes,
	vector<float> & fitnesses
) {
	unsigned int tempIndex;
	float tempFitness;
	for (unsigned int i = 0; i < indexes.size(); i++) {
		for (unsigned int k = 0; k < indexes.size(); k++) {
			if (fitnesses[i] > fitnesses[k]) {
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

unsigned int TournamentSelection::getParent(
	vector<Genome*> population,
	vector<float> fitnesses
) {
	unsigned int populationSize = fitnesses.size();
	unsigned int tournamentSize = min(this->tournamentSize, populationSize);
	vector<float> tempFitnesses;
	vector<unsigned int> indexes;
	unsigned int index;

	for (unsigned int i = 0; i < tournamentSize; i++) {
		index = HierRNG::uniformRandomNumber<
			unsigned int
		>(0, fitnesses.size() - 1);
		tempFitnesses.push_back(fitnesses[index]);
		indexes.push_back(index);
	}

	this->sortByFitness(indexes, tempFitnesses);

	for (unsigned int i = 0; i < indexes.size(); i++)
		if (HierRNG::zeroOne() < this->crossoverRate)
			return indexes[i];

	return indexes[indexes.size() - 1];
}

string TournamentSelection::toString() {
	stringstream ss;

	ss << "Name: " << this->name
	<< "\nTournament size: " << this->tournamentSize
	<< "\nCrossover Rate: " << this->crossoverRate
	<< "\n";

	return ss.str();
}
