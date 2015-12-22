#include <string>
#include "GeneNode.hpp"
#include "PropertiesList.hpp"
#pragma once

/*
* The ToString abstract class serves a similar function to the FitnessFunction
* class - by separating an Individual's ToString from its base functionality,
* the Individual can be left completely generic (with no knowledge of what
* goes on inside of itself).
*/

class ToStringFunction {
	private:

	protected:

	public:
	virtual std::string toString(GeneNode ** pools, int * indexes, int genomeLength)=0;
};
