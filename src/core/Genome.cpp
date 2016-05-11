#include "core/Genome.hpp"
#include "core/Locus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <cmath>
#include <sstream>

using namespace std;

Genome::Genome(vector<Locus*> loci) {
	this->loci = loci;
	generateRandomGenes();
}

Genome::Genome(vector<int> genes, vector<Locus*> loci) {
	this->genes = genes;
	this->loci = loci;
}

Genome::Genome(Genome * other, bool randomize) {
	this->loci = other->getLoci();
	if (randomize) {
		generateRandomGenes();
	} else {
		this->genes = other->getGenome();
	}
}

Genome::Genome(Genome * other, int rawGenes[]) {
	this->loci = other->getLoci();
	vector<int> genes(rawGenes, rawGenes + loci.size());
	for (int i = 0; i < genes.size(); i++) {
		if (this->loci[i]->outOfRange(genes[i])) {
			throw ValueOutOfRangeException();
		}
	}
	this->genes = genes;
}

Genome::~Genome() {}

void Genome::generateRandomGenes() {
	genes.clear();
	for (int i = 0; i < loci.size(); i++) {
		genes.push_back(loci[i]->randomIndex());
	}
}

vector<int> Genome::getGenome() {
	return genes;
}

int Genome::genomeLength() {
	return genes.size();
}

vector<Locus*> Genome::getLoci() {
	return loci;
}

int Genome::difference(Genome * otherGenome) {
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

string Genome::flatten() {
	stringstream ss;

	for (int i = 0; i < genes.size(); i++) {
		ss << loci[i]->flatten(genes[i]) << " ";
	}

	return ss.str();
}
