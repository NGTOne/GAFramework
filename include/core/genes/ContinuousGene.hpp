#ifndef CORE_GENES_ContinuousGene
#define CORE_GENES_ContinuousGene

#include "Gene.hpp"

class ContinuousGene : public Gene {
	private:

	protected:
	void add(double addend);
	void set(double value);

	public:
	template<typename T>
	ContinuousGene(Locus * target, T index);
	ContinuousGene(Gene * other);

	Gene* copy();
	Gene* copy(double newIndex);
};

template<typename T>
ContinuousGene::ContinuousGene(
	Locus * target,
	T index
) : Gene(target, (double)index) {
	static_assert(
		std::is_arithmetic<T>::value,
		"Index type provided to ContinuousGene must be numeric."
	);
}

#endif
