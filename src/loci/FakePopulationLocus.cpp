#include "loci/FakePopulationLocus.hpp"
#include <sstream>

FakePopulationLocus::FakePopulationLocus(
	Genome * target,
	PopulationLocus * original
) : PopulationLocus(original->getNode()) {
	this->target = new Genome(target);
}

FakePopulationLocus::FakePopulationLocus(
	Genome target,
	PopulationLocus * original
) : PopulationLocus(original->getNode()) {
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
	stringstream ss;
	ss << "Fake population locus with genome: "
		<< this->target->flatten()
		<< ".\n";

	return ss.str();
}

std::string FakePopulationLocus::flatten(unsigned int index) {
	return this->target->flatten();
}
