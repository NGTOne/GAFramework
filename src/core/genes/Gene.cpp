#include "core/genes/Gene.hpp"
#include "core/Locus.hpp"
#include "exception/ValueOutOfRangeException.hpp"

Gene::Gene(Locus * target) {
	this->target = target;
	this->index = target->randomIndex();
}

Gene::Gene(Locus * target, double index) {
	this->target = target;
	if (this->validValue(index)) {
		this->index = index;
	} else {
		throw ValueOutOfRangeException();
	}
}

Gene::Gene(Gene * other) {
	this->target = other->getTarget();
	this->index = other->getIndex();
}

double Gene::getIndex() {
	return this->index;
}

Locus * Gene::getTarget() {
	return this->target;
}
