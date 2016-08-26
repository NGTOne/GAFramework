#include <sstream>
#include <numeric>
#include "nodes/EANode/crossovers/UniformCrossover.hpp"
#include "core/utils/HierRNG.hpp"
#include "exception/MismatchedCountsException.hpp"

UniformCrossover::UniformCrossover(
	std::vector<double> parentProbabilities
) : CrossoverOperation() {
	this->init(parentProbabilities);
}

UniformCrossover::UniformCrossover(
	unsigned int numOffspring,
	std::vector<double> parentProbabilities
) : CrossoverOperation(numOffspring) {
	this->init(parentProbabilities);
}

void UniformCrossover::init(std::vector<double> parentProbabilities) {
	if (!parentProbabilities.empty()) {
		double sum = std::accumulate(
			parentProbabilities.begin(),
			parentProbabilities.end(),
			0.0
		);
		if (sum != 1.0) throw ValueOutOfRangeException("Parent probabilities must sum to 1!");
	}

	this->parentProbabilities = parentProbabilities;
}

std::vector<GenomeTemplate> UniformCrossover::crossOver(
	std::vector<GenomeTemplate> parents
) {
	unsigned int shortestGenomeLength = this->shortestGenome(parents);
	if (
		!this->parentProbabilities.empty() &&
		this->parentProbabilities.size() < parents.size()
	) throw MismatchedCountsException("Number of probabilities needs to match the number of parents!");
	std::vector<GenomeTemplate> children;

	for (unsigned int i = 0; i < this->numOffspring; i++) {
		GenomeTemplate child;
		for (unsigned int k = 0; k < shortestGenomeLength; k++)
			if (this->parentProbabilities.empty()) {
				child.add(HierRNG::choose(parents).getGene(k));
			} else {
				child.add(HierRNG::choose(
					parents,
					this->parentProbabilities
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
