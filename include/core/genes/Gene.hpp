#ifndef CORE_GENES_Gene
#define CORE_GENES_Gene

#include "../Locus.hpp"

class Gene {
	private:

	protected:
	Locus * target;
	double index;

	bool validValue(double newIndex);
	double getIndex();
	Locus * getTarget();

	Gene(Locus * target);
	Gene(Locus * target, double index);
	Gene(Gene * other);

	public:
	virtual void add(unsigned int addend)=0;
	virtual void add(double addend)=0;
	virtual void add(int addend)=0;

	virtual void set(unsigned int value)=0;
	virtual void set(double value)=0;
	virtual void set(int value)=0;

	template <typename T>
	T getValue();
};

#endif
