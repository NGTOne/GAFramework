#include <string>
#include "GenePool.hpp"
#include "PropertiesList.hpp"
#pragma once

//This is an abstract class for toString() functions - it is meant to be used
//to prepare a string containing an Individual's genome in some human-readable
//format
class ToStringFunction {
	private:

	protected:

	public:
	virtual std::string toString(GenePool ** pools, int * indexes, int genomeLength)=0;
};
