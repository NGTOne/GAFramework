#include "endconditions/MaxFitnessConvergenceEnd.hpp"

MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(
	double minimumFitness
) : FitnessMatchEnd(minimumFitness) {
	this->populationProportion = 0.5;
}

MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(
	double minimumFitness,
	double populationProportion
) : FitnessMatchEnd(minimumFitness) {
	this->populationProportion = populationProportion;
}

bool MaxFitnessConvergenceEnd::checkCondition(
	std::vector<Genome*> genomes,
	std::vector<Fitness> fitnesses,
	unsigned int currentIteration
) {
	double proportion = 0;
	unsigned int countMadeIt = 0;
	for (unsigned int i = 0; i < genomes.size(); i++)
		if (this->checkSolution(genomes[i], fitnesses[i]))
			countMadeIt++;

	proportion = (double)countMadeIt/(double)genomes.size();

	return proportion >= this->populationProportion;
}
