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
	unsigned seed
) : CrossoverOperation(numOffspring, seed) {}

vector<Genome*> UniformCrossover::crossOver(vector<Genome*> genomes) {
	unsigned int shortestGenomeLength = this->shortestGenome(genomes);
	vector<Genome*> children;
	vector<vector<unsigned int>> parentGenomes = this->getGenomes(genomes);
	vector<vector<Locus*>> parentLoci = this->getLoci(genomes);

	uniform_int_distribution<unsigned int> parentDist(
		0,
		genomes.size() - 1
	);

	for (unsigned int i = 0; i < this->numOffspring; i++) {
		vector<unsigned int> childGenome;
		vector<Locus*> childLoci;
		for (unsigned int k = 0; k < shortestGenomeLength; k++) {
			unsigned int parent = parentDist(this->generator);
			childGenome.push_back(parentGenomes[parent][k]);
			childLoci.push_back(parentLoci[parent][k]);
		}
		children.push_back(new Genome(childGenome, childLoci));
	}

	return children;
}
