#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/crossovers/UniformCrossover.hpp"

using namespace std;

UniformCrossover::UniformCrossover() : CrossoverOperation() {}

UniformCrossover::UniformCrossover(
	unsigned int numOffspring
) : CrossoverOperation(numOffspring) {}

UniformCrossover::UniformCrossover(
	unsigned int numOffspring,
	unsigned int seed
) : CrossoverOperation(numOffspring, seed) {}

std::vector<GenomeTemplate> UniformCrossover::crossOver(
	std::vector<Genome*> genomes
) {
	unsigned int shortestGenomeLength = this->shortestGenome(genomes);
	std::vector<GenomeTemplate> children;
	std::vector<GenomeTemplate> parents = this->getTemplates(genomes);

	uniform_int_distribution<unsigned int> parentDist(
		0,
		genomes.size() - 1
	);

	for (unsigned int i = 0; i < this->numOffspring; i++) {
		GenomeTemplate child;
		for (unsigned int k = 0; k < shortestGenomeLength; k++) {
			unsigned int parent = parentDist(this->generator);
			child.add(parents[parent].getIndex(k));
		}
		children.push_back(child);
	}

	return children;
}

std::string UniformCrossover::toString() {
	stringstream ss;
	ss << "Type: Uniform Crossover\nRandom Seed: " << this->seed
		<< "\nNumber of offspring: " << this->numOffspring << "\n";
	return ss.str();
}
