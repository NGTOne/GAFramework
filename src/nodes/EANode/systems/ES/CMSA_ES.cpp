#include "nodes/EANode/systems/ES/CMSA_ES.hpp"

CMSA_ES::CMSA_ES(
	unsigned int lambda
) : MuCommaLambdaES(new CMSAMutation(lambda), lambda) {}

CMSA_ES::CMSA_ES(
	unsigned int lambda,
	double tau,
	double tauC
) : MuCommaLambdaES(new CMSAMutation(lambda, tau, tauC), lambda) {}

std::vector<Genome*> CMSA_ES::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	((CMSAMutation*)this->mutation)->setMu(initialPopulation.size());
	((CMSAMutation*)this->mutation)->calculateAverages(initialPopulation);

	return ES::breedMutateSelect(
		initialPopulation,
		populationFitnesses,
		objectives,
		speciesNode
	);
}
