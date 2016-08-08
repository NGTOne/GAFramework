#include "loci/FakePopulationLocus.hpp"
#include "core/FakeGenome.hpp"
#include <sstream>

FakePopulationLocus::FakePopulationLocus(
	Genome* target,
	PopulationLocus* original,
	bool fakeGenome
) : PopulationLocus(original->getNode()) {
	this->target = (fakeGenome) ? new FakeGenome(target) : target;
	this->fakeGenome = fakeGenome;
}

FakePopulationLocus::FakePopulationLocus(
	Genome target,
	PopulationLocus* original
) : PopulationLocus(original->getNode()) {
	this->target = new FakeGenome(&target);
	this->fakeGenome = true;
}

FakePopulationLocus::FakePopulationLocus(
	FakePopulationLocus* target
) : PopulationLocus(target->getNode()) {
	this->fakeGenome = target->genomeIsFake();
	Genome* genome = boost::any_cast<Genome*>(target->getIndex(0));
	this->target = (this->fakeGenome) ? new FakeGenome(genome) : genome;
}

FakePopulationLocus::~FakePopulationLocus() {
	if (this->fakeGenome) delete(this->target);
}

bool FakePopulationLocus::isFake() {
	return true;
}

bool FakePopulationLocus::genomeIsFake() {
	return this->fakeGenome;
}

std::string FakePopulationLocus::toString() {
	std::stringstream ss;
	ss << "Fake population locus with genome: "
		<< this->target->flatten()
		<< "\n";

	return ss.str();
}

std::string FakePopulationLocus::flatten(Gene* index) {
	return this->target->flatten();
}

boost::any FakePopulationLocus::getIndex(Gene* index) {
	return this->target;
}
