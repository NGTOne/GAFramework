#include "loci/PopulationLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>

using namespace std;

PopulationLocus::PopulationLocus(PopulationNode * node) {
	this->node = node;
}

PopulationLocus::~PopulationLocus() {}

Genome * PopulationLocus::getIndex(unsigned int index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();
	return this->node->getIndex(index);
}

unsigned int PopulationLocus::topIndex() {
	return this->node->populationSize() - 1;
}

unsigned int PopulationLocus::randomIndex() {
	uniform_int_distribution<unsigned int> dist(
		0,
		this->node->populationSize()-1
	);
	return dist(this->generator);
}

bool PopulationLocus::isConstructive() {
	return true;
}

bool PopulationLocus::outOfRange(unsigned int i) {
	return i >= this->node->populationSize();
}

string PopulationLocus::toString() {
	stringstream ss;
	ss << "Locus uses node " << this->nodeName() << "\n"
		<< "\nRandom Seed: " << seed << "\n";
	return ss.str();
}

string PopulationLocus::nodeName() {
	return this->node->name();
}

string PopulationLocus::flatten(unsigned int index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	stringstream ss;
	ss << this->getIndex(index)->flatten();
	return ss.str();
}

PopulationNode * PopulationLocus::getNode() {
	return this->node;
}
