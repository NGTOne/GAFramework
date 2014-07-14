#include <string>
#include "GenePool.hpp"
#include "PropertiesList.hpp"
#pragma once

//This is an abstract class for fitness functions - as this tends to be the
//only differentiating factor between individuals, it should be extended as
//necessary. The general rule of thumb is "one FitnessFunction per
//HierarchicalGenePool".
class FitnessFunction {
	private:

	protected:

	public:
	virtual PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength)=0;
	virtual std::string toString(GenePool ** pools, int * indexes, int genomeLength)=0;
};
