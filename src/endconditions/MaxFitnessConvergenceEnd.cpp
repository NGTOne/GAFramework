#include "endconditions/MaxFitnessConvergenceEnd.hpp"

MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(
	float minimumFitness
) : FitnessMatchEnd(minimumFitness) {
	this->populationProportion = 0.5;
}

MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(
	float minimumFitness,
	float populationProportion
) : FitnessMatchEnd(minimumFitness) {
	this->populationProportion = populationProportion;
}

bool MaxFitnessConvergenceEnd::checkCondition(
	std::vector<Genome*> genomes,
	std::vector<float> fitnesses,
	unsigned int currentIteration
) {
	float proportion = 0;
	unsigned int countMadeIt = 0;
	for (unsigned int i = 0; i < genomes.size(); i++)
		if (this->checkSolution(genomes[i], fitnesses[i]))
			countMadeIt++;

	proportion = (float)countMadeIt/(float)genomes.size();

	return proportion >= this->populationProportion;
}
