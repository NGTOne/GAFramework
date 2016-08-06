#ifndef CORE_GENES_DiscreteGene
#define CORE_GENES_DiscreteGene

#include "Gene.hpp"

class DiscreteGene : public Gene {
	private:

	protected:
	void add(double addend);
	void set(double value);

	template<typename T, typename = enableIfNumber<T>>
	double round(T value);

	public:
	template<typename T, typename = enableIfNumber<T>>
	DiscreteGene(
		Locus * target,
		T index
	) : Gene(target, this->round(index)) {}
	DiscreteGene(Gene * other);

	template <typename T, typename = enableIfNumber<T>>
	void addToIndex(T addend);

	template <typename T, typename = enableIfNumber<T>>
	void setIndex(T newValue);
};

#endif
