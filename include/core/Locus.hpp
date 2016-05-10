#include <string>
#include <vector>
#include <random>
#include <boost/any.hpp>
#pragma once

class Locus {
	private:

	protected:
	std::vector<boost::any> population;
	std::mt19937 generator;
	unsigned seed;

	Locus();
	Locus(std::vector<boost::any> population);
	void init(unsigned seed);
	void setPopulation(std::vector<boost::any> population);

	boost::any getIndex(int index);

	public:
	~Locus();

	virtual int randomIndex();
	virtual bool outOfRange(int i);
	virtual std::string toString()=0;
};

