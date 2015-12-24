#pragma once
#include "NichingStrategy.hpp"

class Crowding : public NichingStrategy {
	private:

	protected:

	public:
		int * getIndices(
			Individual ** initialPopulation,
			int populationSize,
			Individual ** newIndividuals
		);
};
