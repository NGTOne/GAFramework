#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/crossovers/UniformCrossover.hpp"
#include "core/utils/HierRNG.hpp"
#include "exception/MismatchedCountsException.hpp"

UniformCrossover::UniformCrossover(
	std::vector<double> parentCrossoverProbabilities
) : CrossoverOperation() {
	this->parentCrossoverProbabilities = parentCrossoverProbabilities;
}

UniformCrossover::UniformCrossover(
	unsigned int numOffspring,
	std::vector<double> parentCrossoverProbabilities
) : CrossoverOperation(numOffspring) {
	this->parentCrossoverProbabilities = parentCrossoverProbabilities;
}

std::vector<GenomeTemplate> UniformCrossover::crossOver(
	std::vector<GenomeTemplate> parents
) {
	unsigned int shortestGenomeLength = this->shortestGenome(parents);
	if (
		!this->parentCrossoverProbabilities.empty() &&
		this->parentCrossoverProbabilities.size() < parents.size()
	) throw MismatchedCountsException("Number of probabilities needs to match the genome length!");
	std::vector<GenomeTemplate> children;

	for (unsigned int i = 0; i < this->numOffspring; i++) {
		GenomeTemplate child;
		for (unsigned int k = 0; k < shortestGenomeLength; k++)
			if (this->parentCrossoverProbabilities.empty()) {
				child.add(HierRNG::choose(parents).getGene(k));
			} else {
				child.add(HierRNG::choose(
					parents,
					this->parentCrossoverProbabilities
				).getGene(k));
			}
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
