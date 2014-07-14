#include "../core/SelectionStrategy.hpp"
#include <random>
#include <chrono>
#pragma once

using namespace std;

//Tournament selection is a selection strategy that pits prospective parents
//against each other.Two parents are selected at random, and have their
//fitnesses compared. The parent with the higher fitness is selected for
//crossover, whereas the other is not.
class TournamentSelection : public SelectionStrategy {
	private:

	protected:

	public:

	TournamentSelection(double newCrossoverRate);

        TournamentSelection(unsigned newSeed, double newCrossoverRate);
        
	int getParent(int populationFitnesses[], int populationSize);
};
