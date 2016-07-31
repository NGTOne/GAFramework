#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/SelectionStrategy.hpp"

using namespace std;

SelectionStrategy::SelectionStrategy(double crossoverRate) {
	this->init(crossoverRate, "Unknown");
}

SelectionStrategy::SelectionStrategy(
	double crossoverRate,
	string name
) {
	this->init(crossoverRate, name);
}

SelectionStrategy::~SelectionStrategy() {}

void SelectionStrategy::init(
	double crossoverRate,
	string name
) {
	this->crossoverRate = crossoverRate;
	this->name = name;
}

string SelectionStrategy::toString() {
	stringstream ss;
	ss << "Name: " << name
		<< "\nCrossover Rate: " << crossoverRate << "\n";
	return ss.str();
}
