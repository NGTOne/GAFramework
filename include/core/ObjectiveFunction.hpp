#include <string>
#include "Genome.hpp"
#pragma once

class ObjectiveFunction {
	private:

	protected:

	public:
	virtual int checkFitness(Genome * genome)=0;
	virtual bool isApportioning();
};
