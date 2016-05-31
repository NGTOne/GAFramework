#include "endconditions/FitnessMatchEnd.hpp"

FitnessMatchEnd::FitnessMatchEnd(int minimumFitness) {
	this->minimumFitness = minimumFitness;
}

bool FitnessMatchEnd::checkSolution(Genome * target, int targetFitness) {
	return targetFitness > this->minimumFitness;
}

bool FitnessMatchEnd::checkCondition(
	vector<Genome*> genomes,
	vector<int> fitnesses,
	unsigned int currentIteration
) {
	for (unsigned int i = 0; i < genomes.size(); i++)
		if (this->checkSolution(genomes[i], fitnesses[i])) return true;
	return false;
}
