#include "core/genes/Gene.hpp"
#include "core/Locus.hpp"
#include "exception/ValueOutOfRangeException.hpp"

Gene::Gene(Locus * target) {
	this->target = target;
	this->index = target->randomIndex();
}

Gene::Gene(Locus * target, double index) {
	this->target = target;
	if (!this->valueOutOfRange(index)) {
		this->index = index;
	} else {
		throw ValueOutOfRangeException();
	}
}

Gene::Gene(Gene * other) {
	this->target = other->getLocus();
	this->index = other->getIndex();
}

bool Gene::valueOutOfRange(double newIndex) {
	return this->target->outOfRange(newIndex);
}

double Gene::getIndex() {
	return this->index;
}

Locus * Gene::getLocus() {
	return this->target;
}

bool Gene::isConstructive() {
	return this->target->isConstructive();
}

std::string Gene::flatten() {
	return this->target->flatten(this);
}
