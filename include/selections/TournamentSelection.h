#include "SelectionStrategy.h"
#include <random>
#include <chrono>
#pragma once

using namespace std;

class TournamentSelection : public SelectionStrategy {
	private:

	protected:

	public:

	TournamentSelection();

	TournamentSelection(double newCrossoverRate, int newNumElites);

        TournamentSelection(unsigned newSeed, double newCrossoverRate, int newNumElites);
        
	//Picks two random indices, gets their fitnesses, then compares them
	//and returns the index with the higher fitness
	int getParent(int populationFitnesses[], int populationSize);
};
