#include "core/Locus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <chrono>
#include <sstream>

using namespace std;

Locus::Locus() {
	init(chrono::system_clock::now().time_since_epoch().count());
}

Locus::Locus(vector<boost::any> population) {
	this->population = population;
	init(chrono::system_clock::now().time_since_epoch().count());
}

void Locus::init(unsigned seed) {
	this->seed = seed;
	generator = mt19937(seed);
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
	uniform_int_distribution<unsigned int> dist(
		0,
		this->population.size() - 1
	);
	return dist(this->generator);
}

bool Locus::isConstructive() {
	return false;
}

bool Locus::outOfRange(unsigned int i) {
	return i >= this->population.size();
}
