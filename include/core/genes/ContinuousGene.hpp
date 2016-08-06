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
};

#endif
