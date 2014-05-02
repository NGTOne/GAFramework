#include "Genome.h"
#include <cstdlib>

using namespace std;

Genome::Genome(int * newGene, int newGenomeLength) {
	gene = newGene;
	genomeLength = newGenomeLength;
}

Genome::~Genome() {
	free(gene);
}

int * Genome::getGenome() {
	return gene;
}

int Genome::getGenomeLength() {
	return genomeLength;
}
