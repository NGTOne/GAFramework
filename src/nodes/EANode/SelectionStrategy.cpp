#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/SelectionStrategy.hpp"

SelectionStrategy::SelectionStrategy(double crossoverRate) {
	this->init(crossoverRate, "Unknown");
}

SelectionStrategy::SelectionStrategy(
	double crossoverRate,
	std::string name
) {
	this->init(crossoverRate, name);
}

SelectionStrategy::~SelectionStrategy() {}

void SelectionStrategy::init(
	double crossoverRate,
	std::string name
) {
	this->crossoverRate = crossoverRate;
	this->name = name;
}

std::string SelectionStrategy::toString() {
	std::stringstream ss;
	ss << "Name: " << this->name
		<< "\nCrossover Rate: " << this->crossoverRate << "\n";
	return ss.str();
}
