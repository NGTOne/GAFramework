#include "../core/SelectionStrategy.hpp"
#include <random>
#include <chrono>
#pragma once

using namespace std;

class TournamentSelection : public SelectionStrategy {
	private:

	protected:

	public:

	TournamentSelection(double newCrossoverRate);

        TournamentSelection(unsigned newSeed, double newCrossoverRate);
        
	//Picks two random indices, gets their fitnesses, then compares them
	//and returns the index with the higher fitness
	int getParent(int populationFitnesses[], int populationSize);
};
