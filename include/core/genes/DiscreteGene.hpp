#ifndef CORE_GENES_DiscreteGene
#define CORE_GENES_DiscreteGene

#include "Gene.hpp"
#include "../utils/templates.hpp"

class DiscreteGene : public Gene {
	private:

	protected:
	void add(double addend);
	void set(double value);

	public:
	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	DiscreteGene(Locus* target, T index);
	DiscreteGene(Gene* other);

	Gene* copy();
	Gene* copy(double newIndex);
};

template<typename T, class>
DiscreteGene::DiscreteGene(
	Locus* target,
	T index
) : Gene(target, std::round(index)) {}

#endif
