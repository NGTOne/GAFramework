#include "endconditions/IterationCountEnd.hpp"

IterationCountEnd::IterationCountEnd(unsigned int maxIterations) {
	this->maxIterations = maxIterations;
}

bool IterationCountEnd::checkCondition(
	vector<Genome*> genomes,
	vector<int> fitnesses,
	int currentIteration
) {
	return currentIteration >= this->maxIterations;
}
