#include <string>
#include "Genome.hpp"
#pragma once

class ObjectiveFunction {
	private:

	protected:

	public:
	virtual ~ObjectiveFunction();
	virtual int checkFitness(Genome * genome)=0;
	virtual bool isApportioning();
};
