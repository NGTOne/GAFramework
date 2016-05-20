#include "endconditions/MaxFitnessConvergenceEnd.hpp"

MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(
	int minimumFitness
) : FitnessMatchEnd(minimumFitness) {
	this->populationProportion = 0.5;
}

MaxFitnessConvergenceEnd::MaxFitnessConvergenceEnd(
	int minimumFitness,
	double populationProportion
) : FitnessMatchEnd(minimumFitness) {
	this->populationProportion = populationProportion;
}

bool MaxFitnessConvergenceEnd::checkCondition(
	vector<Genome*> genomes,
	vector<int> fitnesses,
	int currentIteration
) {
	double proportion = 0;
	int countMadeIt = 0;
	for (int i = 0; i < genomes.size(); i++)
		if (this->checkSolution(genomes[i], fitnesses[i]))
			countMadeIt++;

	proportion = (double)countMadeIt/(double)genomes.size();

	return proportion >= this->populationProportion;
}
