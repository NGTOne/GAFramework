#pragma once
#include "../../core/Individual.hpp"

class NichingStrategy {
	private:

	protected:

	public:
		virtual int * getIndices(Individual ** initialPopulation, int populationSize, Individual ** newIndividuals)=0;
};
