#include <random>
#include <chrono>
#include <sstream>
#include "crossovers/UniformCrossover.hpp"

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
	vector<vector<unsigned int>> parentGenomes = this->getGenomes(genomes);
	vector<vector<Locus*>> parentLoci = this->getLoci(genomes);

	uniform_int_distribution<unsigned int> parentDist(
		0,
		genomes.size() - 1
	);

	for (unsigned int i = 0; i < this->numOffspring; i++) {
		GenomeTemplate child;
		for (unsigned int k = 0; k < shortestGenomeLength; k++) {
			unsigned int parent = parentDist(this->generator);
			child.add(
				parentGenomes[parent][k],
				parentLoci[parent][k]
			);
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
