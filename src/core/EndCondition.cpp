#include "core/EndCondition.hpp"

EndCondition::EndCondition() {}

EndCondition::~EndCondition() {}

bool EndCondition::checkSolution(Genome * target, int targetFitness) {
	return false;
}

bool EndCondition::checkCondition(
	std::vector<Genome*> genomes,
	std::vector<int> fitnesses,
	int currentIteration
) {
	return false;
}
