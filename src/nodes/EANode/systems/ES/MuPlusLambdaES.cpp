#include "nodes/EANode/systems/ES/MuPlusLambdaES.hpp"

std::vector<Genome*> MuPlusLambdaES::doReplacement(
	std::vector<Genome*> parents,
	std::vector<Genome*> offspring,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives
) {
	std::vector<Genome*> result, combined(parents);
	std::vector<float> combinedFitnesses(populationFitnesses);
	combined.insert(combined.end(), offspring.begin(), offspring.end());
	for (unsigned int i = 0; i < offspring.size(); i++)
		combinedFitnesses.push_back(this->evaluateFitness(
			offspring[i],
			objectives
		));
	this->sortPopulation(combined, combinedFitnesses);
	for (unsigned int i = 0; i < parents.size(); i++) {
		result.push_back(combined[i]);
		populationFitnesses[i] = combinedFitnesses[i];
	}

	return result;
}
