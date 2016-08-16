#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/crossovers/UniformCrossover.hpp"
#include "core/utils/HierRNG.hpp"

UniformCrossover::UniformCrossover() : CrossoverOperation() {}

UniformCrossover::UniformCrossover(
	unsigned int numOffspring
) : CrossoverOperation(numOffspring) {}

std::vector<GenomeTemplate> UniformCrossover::crossOver(
	std::vector<GenomeTemplate> parents
) {
	unsigned int shortestGenomeLength = this->shortestGenome(parents);
	std::vector<GenomeTemplate> children;

	for (unsigned int i = 0; i < this->numOffspring; i++) {
		GenomeTemplate child;
		for (unsigned int k = 0; k < shortestGenomeLength; k++)
			child.add(HierRNG::choose(parents).getGene(k));
		children.push_back(child);
	}

	return children;
}

std::string UniformCrossover::toString() {
	std::stringstream ss;
	ss << "Type: Uniform Crossover"
		<< "\nNumber of offspring: " << this->numOffspring << "\n";
	return ss.str();
}
