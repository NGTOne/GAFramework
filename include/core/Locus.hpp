#include <string>
#include <vector>
#include <random>
#include <boost/any.hpp>
#include "EABehaviourObject.hpp"
#pragma once

class Locus : public EABehaviourObject {
	private:

	protected:
	std::vector<boost::any> population;
	std::mt19937 generator;
	unsigned int seed;

	Locus();
	Locus(std::vector<boost::any> population);
	void init(unsigned int seed);
	void setPopulation(std::vector<boost::any> population);

	public:
	virtual ~Locus();
	virtual void registerInternalObjects(NodeGarbageCollector & collector);

	virtual unsigned int randomIndex();
	virtual unsigned int topIndex();
	virtual bool outOfRange(unsigned int i);
	virtual bool isConstructive();
	virtual std::string toString()=0;
	virtual std::string flatten(unsigned int index)=0;
	boost::any getIndex(unsigned int index);
};

