#include "loci/PopulationLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>

using namespace std;

PopulationLocus::PopulationLocus(PopulationNode * node) {
	this->node = node;
}

PopulationLocus::~PopulationLocus() {}

Genome * PopulationLocus::getIndex(int index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();
	return this->node->getIndex(index);
}

int PopulationLocus::topIndex() {
	return this->node->populationSize() - 1;
}

int PopulationLocus::randomIndex() {
	uniform_int_distribution<int> dist(0, this->node->populationSize()-1);
	return dist(this->generator);
}

bool PopulationLocus::isConstructive() {
	return true;
}

bool PopulationLocus::outOfRange(int i) {
	return i < 0 || i >= this->node->populationSize();
}

string PopulationLocus::toString() {
	stringstream ss;

	for (int i = 0; i < population.size(); i++) {
		ss << "Locus uses node " << this->nodeName();
	}

	ss << "\nRandom Seed: " << seed << "\n";

	return ss.str();
}

string PopulationLocus::nodeName() {
	return this->node->name();
}

string PopulationLocus::flatten(int index) {
	if (outOfRange(index)) throw ValueOutOfRangeException();

	stringstream ss;
	ss << this->getIndex(index)->flatten();
	return ss.str();
}
