#include "core/genes/ContinuousGene.hpp"
#include "core/Locus.hpp"
#include "core/utils/HierRNG.hpp"
#include <limits>

ContinuousGene::ContinuousGene(Gene * other) : Gene(other) {}

void ContinuousGene::add(double addend) {
	this->index = this->target->closestIndex(this->index + addend);
}

void ContinuousGene::set(double value) {
	this->index = this->target->closestIndex(value);
}

Gene* ContinuousGene::copy() {
	return new ContinuousGene(this);
}

Gene* ContinuousGene::copy(double newIndex) {
	return new ContinuousGene(
		this->target,
		this->target->closestIndex(newIndex)
	);
}

// TODO: Figure out if this implementation actually makes the most sense
// Maybe an arbitrary deterministic increment works better
Gene* ContinuousGene::increment() {
	this->add(HierRNG::uniform(
		std::numeric_limits<double>::epsilon(),
		1.0
	));
	return this;
}

Gene* ContinuousGene::decrement() {
	this->add(HierRNG::uniform(
		-std::numeric_limits<double>::epsilon(),
		-1.0
	));
	return this;
}
