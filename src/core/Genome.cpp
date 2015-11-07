#include "core/Genome.hpp"
#include <cstdlib>
#include <cmath>

using namespace std;

Genome::Genome(int * newGene, int newGenomeLength, GenePool ** newGenePools) {
	gene = (int*)malloc(sizeof(int)*newGenomeLength);

	for (int i = 0; i < newGenomeLength; i++) {
		gene[i] = newGene[i];
	}

	genomeLength = newGenomeLength;
	genePools = newGenePools;
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

GenePool ** Genome::getGenePools() {
	return genePools;
}

int Genome::getDifference(Genome * otherGenome) {
	int * otherGenomeRaw = otherGenome->getGenome();
	int otherGenomeLength = otherGenome->getGenomeLength();
	int difference = 0;
	int shorterGenome = fmin(genomeLength, otherGenomeLength);
	int longerGenome = fmax(genomeLength, otherGenomeLength);
	int i;

	for (i = 0; i < shorterGenome; i++) {
		difference += abs(gene[i] - otherGenomeRaw[i]);
	}

	// We want to account for genes of different lengths somehow
	if (longerGenome != shorterGenome) {
		difference += longerGenome - shorterGenome;
	}

	return difference;
}
