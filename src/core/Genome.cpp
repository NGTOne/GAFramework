#include "Genome.h"
#include <cstdlib>

using namespace std;

Genome::Genome(int * newGene, int newGenomeLength) {
	gene = (int*)malloc(sizeof(int)*newGenomeLength);

	for (int i = 0; i < newGenomeLength; i++) {
		gene[i] = newGene[i];
	}

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
