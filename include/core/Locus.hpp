#ifndef CORE_Locus
#define CORE_Locus

#include <string>
#include <vector>
#include <random>
#include <boost/any.hpp>
#include "EABehaviourObject.hpp"
#include "genes/Gene.hpp"

class Gene;

class Locus : public EABehaviourObject {
	private:

	protected:
	Locus();

	public:
	virtual ~Locus();
	virtual Gene* getGene()=0;
	virtual Gene* getGene(double index)=0;

	virtual double randomIndex()=0;
	virtual double topIndex()=0;
	virtual double bottomIndex()=0;
	virtual double closestIndex(double index)=0;
	virtual bool outOfRange(double index)=0;
	virtual bool outOfRange(Gene* index);
	virtual bool isConstructive();
	virtual std::string toString()=0;
	virtual std::string flatten(Gene* index)=0;
	virtual boost::any getIndex(Gene* index)=0;
};

#endif
