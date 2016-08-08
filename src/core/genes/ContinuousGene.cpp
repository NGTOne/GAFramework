#include "core/genes/ContinuousGene.hpp"
#include "core/Locus.hpp"

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
