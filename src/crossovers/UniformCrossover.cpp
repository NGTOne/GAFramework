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
	int shortestGenomeLength = this->shortestGenome(genomes);
	vector<Genome*> children;
	vector<vector<int>> parentGenomes = this->getGenomes(genomes);
	vector<vector<Locus*>> parentLoci = this->getLoci(genomes);

	uniform_int_distribution<int> parentDist(0, genomes.size() - 1);

	for (int i = 0; i < this->numOffspring; i++) {
		vector<int> childGenome;
		vector<Locus*> childLoci;
		for (int k = 0; k < shortestGenomeLength; k++) {
			int parent = parentDist(this->generator);
			childGenome.push_back(parentGenomes[parent][k]);
			childLoci.push_back(parentLoci[parent][k]);
		}
		children.push_back(new Genome(childGenome, childLoci));
	}

	return children;
}
