#ifndef CORE_GENES_ContinuousGene
#define CORE_GENES_ContinuousGene

#include "Gene.hpp"
#include "../utils/templates.hpp"

class ContinuousGene : public Gene {
	private:

	protected:
	void add(double addend);
	void set(double value);

	public:
	template<typename T, typename = EnableIf<std::is_arithmetic<T>>>
	ContinuousGene(Locus * target, T index);
	ContinuousGene(Gene * other);

	Gene* copy();
	Gene* copy(double newIndex);
};

template<typename T, class>
ContinuousGene::ContinuousGene(
	Locus * target,
	T index
) : Gene(target, (double)index) {}

#endif
