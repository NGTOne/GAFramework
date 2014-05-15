//This is an abstract class for fitness functions - should be extended as
//necessary, with one subclass per "species" of individual

#include <string>
#include "GenePool.hpp"
#pragma once

class FitnessFunction {
	private:

	protected:

	public:
	virtual int * checkFitness(GenePool ** pools, int * indexes, int genomeLength)=0;
	virtual std::string toString(GenePool ** pools, int * indexes, int genomeLength)=0;
};
