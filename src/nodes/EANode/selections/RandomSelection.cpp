#include "nodes/EANode/selections/RandomSelection.hpp"
#include "core/utils/HierRNG.hpp"
#include <random>
#include <sstream>

RandomSelection::RandomSelection() : SelectionStrategy(0, "Random") {}

unsigned int RandomSelection::getParent(
	std::vector<Genome*> population,
	std::vector<float> fitnesses
) {
	return HierRNG::index(population.size() - 1);
}

std::string RandomSelection::toString() {
	std::stringstream ss;
	ss << "Name: " << this->name <<"\n";
	return ss.str();
}
