#include "SelectionStrategy.h"
#include <random>
#include <chrono>

using namespace std;

class TournamentSelection : SelectionStrategy {
	private:

	protected:

	public:

	//Picks two random indices, gets their fitnesses, then compares them
	//and returns the index with the higher fitness
	int getParent(int populationFitnesses[], int populationSize);
};
