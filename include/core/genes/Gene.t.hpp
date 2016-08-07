#ifndef CORE_GENES_Gene_t
#define CORE_GENES_Gene_t

#include "../Locus.hpp"
#include "Gene.hpp"

template <typename T>
T Gene::getValue() {
	return boost::any_cast<T>(this->target->getIndex(this));
}

template<typename T, class>
void Gene::addToIndex(T addend) {
	this->add((double)addend);
}

template<typename T, class>
void Gene::setIndex(T value) {
	this->set((double)value);
}

#endif
