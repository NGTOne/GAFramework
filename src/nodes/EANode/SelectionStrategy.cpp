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

std::vector<Genome*> SelectionStrategy::chooseParents(
	std::vector<Genome*> population,
	std::vector<float> fitnesses,
	unsigned int count
) {
	if (count >= population.size()) return population;
	std::vector<Genome*> parents;

	for (unsigned int i = 0; i < count; i++)
		parents.push_back(population[this->getParent(
			population,
			fitnesses
		)]);

	return parents;
}

std::string SelectionStrategy::toString() {
	std::stringstream ss;
	ss << "Name: " << this->name
		<< "\nCrossover Rate: " << this->crossoverRate << "\n";
	return ss.str();
}
