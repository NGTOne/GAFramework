#include "endconditions/FitnessMatchEnd.hpp"

FitnessMatchEnd::FitnessMatchEnd(float minimumFitness) {
	this->minimumFitness = minimumFitness;
}

bool FitnessMatchEnd::checkSolution(Genome* target, float targetFitness) {
	return targetFitness > this->minimumFitness;
}

bool FitnessMatchEnd::checkCondition(
	std::vector<Genome*> genomes,
	std::vector<float> fitnesses,
	unsigned int currentIteration
) {
	for (unsigned int i = 0; i < genomes.size(); i++)
		if (this->checkSolution(genomes[i], fitnesses[i])) return true;
	return false;
}
