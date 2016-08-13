#ifndef CORE_GENES_DiscreteGene
#define CORE_GENES_DiscreteGene

#include "Gene.hpp"

class DiscreteGene : public Gene {
	private:

	protected:
	void add(double addend);
	void set(double value);

	public:
	template<typename T>
	DiscreteGene(Locus* target, T index);
	DiscreteGene(Gene* other);

	Gene* copy();
	Gene* copy(double newIndex);
};

template<typename T>
DiscreteGene::DiscreteGene(
	Locus* target,
	T index
) : Gene(target, std::round(index)) {
	static_assert(
		std::is_arithmetic<T>::value,
		"Index type provided to DiscreteGene must be numeric."
	);
}

#endif
