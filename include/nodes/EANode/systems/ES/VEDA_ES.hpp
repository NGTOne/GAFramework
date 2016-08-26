#ifndef NODES_EANODE_SYSTEMS_ES_VEDA_ES
#define NODES_EANODE_SYSTEMS_ES_VEDA_ES

#include "MuPlusLambdaES.hpp"

class VEDA_ES: public MuPlusLambdaES {
	private:

	protected:

	public:
	VEDA_ES(unsigned int lambda, CrossoverOperation* cross = NULL);
	VEDA_ES(
		unsigned int lambda,
		double tau,
		double tauC,
		CrossoverOperation* cross = NULL
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};

#endif
