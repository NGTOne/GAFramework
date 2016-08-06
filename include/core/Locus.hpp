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
	std::vector<boost::any> population;

	Locus();
	Locus(std::vector<boost::any> population);
	void setPopulation(std::vector<boost::any> population);

	public:
	virtual ~Locus();
	virtual Gene* getGene()=0;
	virtual Gene* getGene(double index)=0;

	virtual double randomIndex()=0;
	virtual double topIndex()=0;
	virtual double bottomIndex()=0;
	virtual bool outOfRange(double i);
	virtual bool isConstructive();
	virtual std::string toString()=0;
	virtual std::string flatten(Gene* index)=0;
	boost::any getIndex(Gene* index);
};

#endif
