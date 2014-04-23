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
	init(newCrossoverRate, seed, "Unknown");
}

SelectionStrategy::SelectionStrategy(unsigned newSeed, double newCrossoverRate)  {
	init(newCrossoverRate, newSeed, "Unknown");
}

SelectionStrategy::SelectionStrategy(unsigned newSeed, double newCrossoverRate, string newName) {
	init(newCrossoverRate, newSeed, newName);
}

void SelectionStrategy::init(double newCrossoverRate, unsigned newSeed, string newName) {
	seed = newSeed;
	crossoverRate = newCrossoverRate;
	mt19937 newGenerator(seed);
	generator = newGenerator;
	name = newName;
}

string SelectionStrategy::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Name: " << name << "\nRandom seed: " << seed << "\nCrossover Rate: " << crossoverRate << "\n";

	returnString = ss.str();

	return returnString;
}
