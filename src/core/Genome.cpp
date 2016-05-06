#include "core/Genome.hpp"
#include "core/Locus.hpp"
#include <cstdlib>
#include <cmath>

using namespace std;

Genome::Genome(vector<Locus*> loci) {
	this->loci = loci;
	for (int i = 0; i < loci.size(); i++) {
		genes.push_back(loci[i]->randomIndex());
	}
}

Genome::Genome(vector<int> genes, vector<Locus*> loci) {
	this->genes = genes;
	this->loci = loci;
}

Genome::~Genome() {}

vector<int> Genome::getGenome() {
	return genes;
}

int Genome::getGenomeLength() {
	return genes.size();
}

vector<Locus*> Genome::getLoci() {
	return loci;
}

int Genome::getDifference(Genome * otherGenome) {
	vector<int> otherGenes = otherGenome->getGenome();
	int difference = 0;
	int shorterGenome = fmin(genes.size(), otherGenes.size());
	int longerGenome = fmax(genes.size(), otherGenes.size());
	int i;

	for (i = 0; i < shorterGenome; i++) {
		difference += abs(genes[i] - otherGenes[i]);
	}

	// We want to account for genes of different lengths somehow
	if (longerGenome != shorterGenome) {
		difference += longerGenome - shorterGenome;
	}

	return difference;
}
