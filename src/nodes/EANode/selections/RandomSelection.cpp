#include "nodes/EANode/selections/RandomSelection.hpp"
#include "core/HierRNG.hpp"
#include <random>
#include <sstream>

RandomSelection::RandomSelection() : SelectionStrategy(0, "Random") {}

unsigned int RandomSelection::getParent(
	std::vector<Genome*> population,
	std::vector<float> fitnesses
) {
	return HierRNG::uniformRandomNumber<
		unsigned int
	>(0, population.size() - 1);
}

std::string RandomSelection::toString() {
	stringstream ss;
	ss << "Name: " << this->name <<"\n";
	return ss.str();
}
