#include "loci/PopulationLocus.hpp"
#include <boost/any.hpp>
#include <sstream>

using namespace std;

PopulationLocus::PopulationLocus(PopulationNode * node) {
	this->node = node;
}

PopulationLocus::~PopulationLocus() {}

Genome * PopulationLocus::getIndex(int index) {
	return this->node->getIndex(index);
}

int PopulationLocus::randomIndex() {
	uniform_int_distribution<int> dist(0, this->node->populationSize());
	return dist(this->generator);
}

bool PopulationLocus::outOfRange(int i) {
	return i < 0 || i >= this->node->populationSize();
}

string PopulationLocus::toString() {
	stringstream ss;

	for (int i = 0; i < population.size(); i++) {
		ss << "Locus uses node " << this->node->name();
	}

	ss << "\nRandom Seed: " << seed << "\n";

	return ss.str();
}
