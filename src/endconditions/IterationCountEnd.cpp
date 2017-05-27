#include "endconditions/IterationCountEnd.hpp"

IterationCountEnd::IterationCountEnd(unsigned int maxIterations) {
	this->maxIterations = maxIterations;
}

bool IterationCountEnd::checkCondition(
	std::vector<Genome*> genomes,
	std::vector<Fitness> fitnesses,
	unsigned int currentIteration
) {
	return currentIteration >= this->maxIterations;
}
