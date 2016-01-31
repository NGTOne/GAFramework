#include "systems/AccelSSGA.hpp"

AccelSSGA::AccelSSGA(SelectionStrategy * strategy) : SSGA(strategy) {}

AccelSSGA::AccelSSGA(
	unsigned seed,
	SelectionStrategy * strategy
) : SSGA(seed, strategy) {}

AccelSSGA::AccelSSGA(
	SelectionStrategy * strategy,
	NichingStrategy * niching
) : SSGA(strategy, niching) {}

AccelSSGA::AccelSSGA(
	unsigned seed,
	SelectionStrategy * strategy,
	NichingStrategy * niching
) : SSGA(seed, strategy, niching) {}

Individual ** AccelSSGA::breedMutateSelect(
	Individual ** initialPopulation,
	int * populationFitnesses,
	int populationSize
) {
	Individual ** newPopulation = NULL;
	for (int i = 0; i < populationSize/2; i++) {
		if (!newPopulation) {
			newPopulation = SSGA::breedMutateSelect(
				initialPopulation,
				populationFitnesses,
				populationSize
			);
		} else {
			Individual ** tempPopulation = SSGA::breedMutateSelect(
				newPopulation,
				populationFitnesses,
				populationSize
			);

			for (int k = 0; k < populationSize; k++) {
				delete(newPopulation[k]);
			}
			free(newPopulation);
			newPopulation = tempPopulation;
		}
	}

	return newPopulation;
}
