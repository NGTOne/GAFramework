#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/SelectionStrategy.hpp"

using namespace std;

SelectionStrategy::SelectionStrategy(double crossoverRate) {
	this->seed = chrono::system_clock::now().time_since_epoch().count();
	init(crossoverRate, seed, "Unknown");
}

SelectionStrategy::SelectionStrategy(double crossoverRate, unsigned seed)  {
	init(crossoverRate, seed, "Unknown");
}

SelectionStrategy::SelectionStrategy(
	double crossoverRate,
	string name
) {
	init(
		crossoverRate,
		chrono::system_clock::now().time_since_epoch().count(),
		name
	);
}

SelectionStrategy::SelectionStrategy(
	unsigned seed,
	double crossoverRate,
	string name
) {
	init(crossoverRate, seed, name);
}

SelectionStrategy::~SelectionStrategy() {}

void SelectionStrategy::init(
	double crossoverRate,
	unsigned seed,
	string name
) {
	this->seed = seed;
	this->crossoverRate = crossoverRate;
	this->generator = mt19937(seed);
	this->name = name;
}

string SelectionStrategy::toString() {
	stringstream ss;
	ss << "Name: " << name << "\nRandom seed: " << seed
		<< "\nCrossover Rate: " << crossoverRate << "\n";
	return ss.str();
}
