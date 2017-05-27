#include "endconditions/FitnessMatchEnd.hpp"

FitnessMatchEnd::FitnessMatchEnd(double minimumFitness) {
	this->minimumFitness = minimumFitness;
}

bool FitnessMatchEnd::checkSolution(Genome* target, Fitness targetFitness) {
	return targetFitness.collapse() > this->minimumFitness;
}

bool FitnessMatchEnd::checkCondition(
	std::vector<Genome*> genomes,
	std::vector<Fitness> fitnesses,
	unsigned int currentIteration
) {
	for (unsigned int i = 0; i < genomes.size(); i++)
		if (this->checkSolution(genomes[i], fitnesses[i])) return true;
	return false;
}
