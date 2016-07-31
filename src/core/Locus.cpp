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

unsigned int Locus::topIndex() {
	return this->population.size() - 1;
}

unsigned int Locus::randomIndex() {
	return HierRNG::index(this->topIndex());
}

bool Locus::isConstructive() {
	return false;
}

bool Locus::outOfRange(unsigned int i) {
	return i >= this->population.size();
}
