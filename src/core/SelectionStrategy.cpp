//This abstract class serves as a general base for all selection strategies,
//allowing any HierarchicalGenePool to use any strategy you might want

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "SelectionStrategy.h"

using namespace std;

SelectionStrategy::SelectionStrategy(double newCrossoverRate) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(newCrossoverRate, seed);
}

SelectionStrategy::SelectionStrategy(unsigned newSeed, double newCrossoverRate)  {
	init(newCrossoverRate, newSeed);
}

void SelectionStrategy::init(double newCrossoverRate, unsigned newSeed) {
	seed = newSeed;
	crossoverRate = newCrossoverRate;
	mt19937 newGenerator(seed);
	generator = newGenerator;
}
