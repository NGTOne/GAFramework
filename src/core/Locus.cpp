#include "core/Locus.hpp"
#include "core/HierRNG.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <chrono>
#include <sstream>

using namespace std;

Locus::Locus() {}

Locus::Locus(vector<boost::any> population) {
	this->population = population;
}

void Locus::setPopulation(vector<boost::any> population) {
	this->population = population;
}

boost::any Locus::getIndex(unsigned int index) {
	return this->population[index];
}

Locus::~Locus() {}

void Locus::registerInternalObjects(NodeGarbageCollector & collector) {}

unsigned int Locus::topIndex() {
	return this->population.size() - 1;
}

unsigned int Locus::randomIndex() {
	return HierRNG::uniformRandomNumber<unsigned int>(0, this->topIndex());
}

bool Locus::isConstructive() {
	return false;
}

bool Locus::outOfRange(unsigned int i) {
	return i >= this->population.size();
}
