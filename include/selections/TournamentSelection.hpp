#include "../core/SelectionStrategy.hpp"
#include <random>
#include <chrono>
#pragma once

/*
* The tournament selection strategy selects two individuals, compares them
* by their fitness, and then selects the one with the higher fitness for
* crossover.
*/

using namespace std;

class TournamentSelection : public SelectionStrategy {
	private:

	protected:

	public:

	TournamentSelection(double newCrossoverRate);

        TournamentSelection(unsigned newSeed, double newCrossoverRate);
        
	int getParent(int populationFitnesses[], int populationSize);
};
