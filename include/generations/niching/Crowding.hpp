#pragma once
#include "generations/niching/NichingStrategy.hpp"

class Crowding : NichingStrategy {
	private:

	protected:

	public:
		int * getIndices(Individual ** initialPopulation, int populationSize, Individual ** newIndividuals);
};
