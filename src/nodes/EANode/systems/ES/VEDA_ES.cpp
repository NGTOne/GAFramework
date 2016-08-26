#include "nodes/EANode/systems/ES/VEDA_ES.hpp"

VEDA_ES::VEDA_ES(
	unsigned int lambda
) : MuCommaLambdaES(new VEDAMutation(lambda), lambda) {}

VEDA_ES::VEDA_ES(
	unsigned int lambda,
	double tau,
	double tauC
) : MuCommaLambdaES(new VEDAMutation(lambda, tau, tauC), lambda) {}

std::vector<Genome*> VEDA_ES::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	((VEDAMutation*)this->mutation)->setMu(initialPopulation.size());
	((VEDAMutation*)this->mutation)->calculateAverages(initialPopulation);

	return ES::breedMutateSelect(
		initialPopulation,
		populationFitnesses,
		objectives,
		speciesNode
	);
}
