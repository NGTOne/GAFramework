#include "core/genes/DiscreteGene.hpp"

DiscreteGene::DiscreteGene(Gene * other) : Gene(other) {}

void DiscreteGene::add(double addend) {
	this->index = std::round(
		this->target->closestIndex(this->index + addend)
	);
}

void DiscreteGene::set(double value) {
	this->index = std::round(this->target->closestIndex(value));
}
