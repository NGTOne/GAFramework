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

Gene* DiscreteGene::copy() {
	return new DiscreteGene(this);
}

Gene* DiscreteGene::copy(double newIndex) {
	return new DiscreteGene(
		this->target,
		this->target->closestIndex(newIndex)
	);
}

Gene* DiscreteGene::increment() {
	this->add(1);
	return this;
}

Gene* DiscreteGene:: decrement() {
	this->add(-1);
	return this;
}
