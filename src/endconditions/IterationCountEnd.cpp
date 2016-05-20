#include "endconditions/IterationCountEnd.hpp"

IterationCountEnd::IterationCountEnd(unsigned int minimumFitness) {
	this->maxIterations = maxIterations;
}

bool IterationCountEnd::checkCondition(
	vector<Genome*> genomes,
	vector<int> fitnesses,
	int currentIteration
) {
	return currentIteration >= maxIterations;
}
