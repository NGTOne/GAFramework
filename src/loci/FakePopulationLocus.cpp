#include "loci/FakePopulationLocus.hpp"
#include <sstream>

FakePopulationLocus::FakePopulationLocus(Genome * target) {
	this->target = new Genome(target);
}

FakePopulationLocus::FakePopulationLocus(Genome target) {
	this->target = new Genome(&target);
}

FakePopulationLocus::~FakePopulationLocus() {
	delete(this->target);
}

Genome * FakePopulationLocus::getIndex(unsigned int index) {
	return this->target;
}

unsigned int FakePopulationLocus::randomIndex() {
	return 0;
}

unsigned int FakePopulationLocus::topIndex() {
	return 0;
}

bool FakePopulationLocus::outOfRange(unsigned int i) {
	return false;
}

bool FakePopulationLocus::isFake() {
	return true;
}

std::string FakePopulationLocus::toString() {
	return "Fake population locus.";
}

std::string FakePopulationLocus::flatten(unsigned int index) {
	return "";
}

Genome FakePopulationLocus::flattenToGenome(unsigned int index) {
	return this->target->flattenGenome();
}
