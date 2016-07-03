#include <string>
#include "Genome.hpp"
#pragma once

class ObjectiveFunction {
	private:

	protected:

	public:
	virtual ~ObjectiveFunction();
	virtual float checkFitness(Genome * genome)=0;
	virtual bool isApportioning();
	virtual bool isNested();
};
