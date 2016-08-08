#include "core/Locus.hpp"

Locus::Locus() {}

Locus::~Locus() {}

bool Locus::isConstructive() {
	return false;
}

bool Locus::outOfRange(Gene* index) {
	return this->outOfRange(index->getIndex());
}
