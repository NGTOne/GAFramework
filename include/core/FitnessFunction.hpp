//This is an abstract class for fitness functions - should be extended as
//necessary, with one subclass per "species" of individual

#include <string>
#include "GenePool.hpp"
#include "PropertiesList.hpp"
#pragma once

class FitnessFunction {
	private:

	protected:

	public:
	virtual PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength)=0;
	virtual std::string toString(GenePool ** pools, int * indexes, int genomeLength)=0;
};
