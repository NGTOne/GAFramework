#include "../core/SelectionStrategy.hpp"
#include <random>
#include <chrono>
#include <string>
#pragma once

/*
* The tournament selection strategy selects two individuals, compares them
* by their fitness, and then selects the one with the higher fitness for
* crossover.
*/

class TournamentSelection : public SelectionStrategy {
	private:

	protected:
	int tournamentSize;
	void sortByFitness(int indexes[], int fitnesses[]);

	void init(int newTournamentSize);

	public:
	TournamentSelection(double newCrossoverRate);
        TournamentSelection(unsigned newSeed, double newCrossoverRate);
	TournamentSelection(double newCrossoverRate, int newTournamentSize);
	TournamentSelection(
		unsigned newSeed,
		double newCrossoverRate,
		int newTournamentSize
	);
        
	int getParent(int populationFitnesses[], int populationSize);

	std::string toString();
};
