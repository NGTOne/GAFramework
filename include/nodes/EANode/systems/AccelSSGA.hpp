#ifndef NODES_EANODE_SYSTEMS_AccelSSGA
#define NODES_EANODE_SYSTEMS_AccelSSGA

#include "SSGA.hpp"
#include "niching/NichingStrategy.hpp"
#include <vector>

/*
* The "Accelerated SSGA" model uses the steady-state GA model, in which one pair
* of parents is directly replaced by their offspring in each generation. For
* this reason, it is much slower than other models, but can yield results
* that may not appear using them.
*
* The big difference between this and "standard" SSGA is that it performs
* n/2 operations (where n is the population size) rather than just 1 operation
* per generation
*/

class AccelSSGA : public SSGA {
	private:

	protected:

	public:
	AccelSSGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);
	AccelSSGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		NichingStrategy * niching
	);

	virtual std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float> & populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};

#endif
