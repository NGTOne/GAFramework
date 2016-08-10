#ifndef CORE_GENES_Gene_t
#define CORE_GENES_Gene_t

#include "../Locus.hpp"
#include "Gene.hpp"

template <typename T>
T Gene::getValue() {
	return boost::any_cast<T>(this->target->getIndex(this));
}

template<typename T>
void Gene::addToIndex(T addend) {
	static_assert(
		std::is_arithmetic<T>::value,
		"Value added to index must be a number."
	);
	this->add((double)addend);
}

template<typename T>
void Gene::setIndex(T value) {
	static_assert(
		std::is_arithmetic<T>::value,
		"Value designated as index must be a number."
	);
	this->set((double)value);
}

#endif
