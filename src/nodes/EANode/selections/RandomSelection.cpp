#include "nodes/EANode/selections/RandomSelection.hpp"
#include <random>
#include <sstream>

RandomSelection::RandomSelection() : SelectionStrategy(0, "Random") {}

unsigned int RandomSelection::getParent(
	std::vector<Genome*> population,
	std::vector<float> fitnesses
) {
	std::uniform_int_distribution<unsigned int> parentDist(
		0,
		population.size() - 1
	);
	return parentDist(this->generator);
}

std::string RandomSelection::toString() {
	stringstream ss;

	ss << "Name: " << this->name
		<< " Random Seed: " << this->seed
		<<"\n";

	return ss.str();
}
