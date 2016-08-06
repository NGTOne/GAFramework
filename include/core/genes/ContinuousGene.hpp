#ifndef CORE_GENES_ContinuousGene
#define CORE_GENES_ContinuousGene

#include "Gene.hpp"

class ContinuousGene : public Gene {
	private:

	protected:
	void add(double addend);
	void set(double value);

	public:
	template<typename T, typename = enableIfNumber<T>>
	ContinuousGene(
		Locus * target,
		T index
	) : Gene(target, (double)index)  {}
	ContinuousGene(Gene * other);
};

#endif
