#ifndef CORE_GENES_DiscreteGene
#define CORE_GENES_DiscreteGene

#include "Gene.hpp"
#include "../utils/templates.hpp"

class DiscreteGene : public Gene {
	private:

	protected:
	void add(double addend);
	void set(double value);

	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	double round(T value);

	public:
	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	DiscreteGene(Locus * target, T index);
	DiscreteGene(Gene * other);

	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	void addToIndex(T addend);

	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	void setIndex(T newValue);
};

#endif
