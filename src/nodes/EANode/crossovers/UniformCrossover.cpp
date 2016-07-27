#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/crossovers/UniformCrossover.hpp"
#include "core/HierRNG.hpp"

using namespace std;

UniformCrossover::UniformCrossover() : CrossoverOperation() {}

UniformCrossover::UniformCrossover(
	unsigned int numOffspring
) : CrossoverOperation(numOffspring) {}

std::vector<GenomeTemplate> UniformCrossover::crossOver(
	std::vector<Genome*> genomes
) {
	unsigned int shortestGenomeLength = this->shortestGenome(genomes);
	std::vector<GenomeTemplate> children;
	std::vector<GenomeTemplate> parents = this->getTemplates(genomes);

	for (unsigned int i = 0; i < this->numOffspring; i++) {
		GenomeTemplate child;
		for (unsigned int k = 0; k < shortestGenomeLength; k++) {
			unsigned int parent = HierRNG::index(genomes.size()-1);
			child.add(parents[parent].getIndex(k));
		}
		children.push_back(child);
	}

	return children;
}

std::string UniformCrossover::toString() {
	stringstream ss;
	ss << "Type: Uniform Crossover"
		<< "\nNumber of offspring: " << this->numOffspring << "\n";
	return ss.str();
}
