#include "../core/GenerationModel.hpp"
#include <random>
#include <string>
#pragma once

//This generation model is a (mu/rho+, lambda)-ES, derived from the work of
//Rechenberg et al. in the 1960s and 1970s. It works by creating a new
//population of offspring, separate from the parents, then combining the
//populations, sorting them, and truncating to the original population size.
//NOTE: Due to this mechanism, it has a higher memory cost than either GA or
//SSGA, and this should be taken into account for larger problems or older
//computers.
class ESGeneration : public GenerationModel {
	private:

	protected:

	public:

	ESGeneration(SelectionStrategy * newStrategy);

	ESGeneration(unsigned newSeed, SelectionStrategy * newStrategy);

	Individual ** breedMutateSelect(Individual ** initialPopulation, int * populationFitnesses, int populationSize);
};
