#include "core/Genome.hpp"
#include "core/Locus.hpp"
#include "loci/PopulationLocus.hpp"
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

Genome::Genome(Genome * other) {
	this->loci = other->getLoci();
	this->genes = other->getGenome();
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

	for (int i = 0; i < genes.size(); i++)
		ss << loci[i]->flatten(genes[i]) << " ";

	return ss.str();
}

Genome Genome::flattenGenome() {
	vector<int> rawGenome;
	vector<Locus*> rawLoci;

	for (int i = 0; i < this->genomeLength(); i++) {
		if (!loci[i]->isConstructive()) {
			rawGenome.push_back(this->genes[i]);
			rawLoci.push_back(this->loci[i]);
		} else {
			Genome * temp = ((PopulationLocus*)loci[i])->getIndex(
				this->genes[i]
			);

			Genome tempFlattened = temp->flattenGenome();
			vector<int> tempGenome = tempFlattened.getGenome();
			vector<Locus*> tempLoci = tempFlattened.getLoci();

			for (int k = 0; k < tempGenome.size(); k++) {
				rawGenome.push_back(tempGenome[k]);
				rawLoci.push_back(tempLoci[k]);
			}
		}
	}

	return Genome(rawGenome, rawLoci);
}

bool Genome::usesComponent(Genome * component) {
	for (int i = 0; i < this->loci.size(); i++) {
		Locus * locus = this->loci[i];
		if (locus->isConstructive()) {
			Genome * temp = ((PopulationLocus*)locus)->getIndex(
				this->genes[i]
			);

			return (temp == component) ?
				true : temp->usesComponent(component);
		}
	}

	return false;
}
