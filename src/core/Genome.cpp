#include "core/Genome.hpp"
#include "core/Locus.hpp"
#include "loci/PopulationLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "exception/ComponentNotPresentException.hpp"
#include <cmath>
#include <sstream>

using namespace std;

Genome::Genome(vector<Locus*> loci, std::string speciesNode) {
	this->loci = loci;
	this->speciesNode = speciesNode;
	generateRandomGenes();
}

Genome::Genome(
	vector<unsigned int> genes,
	vector<Locus*> loci,
	std::string speciesNode
) {
	this->genes = genes;
	this->loci = loci;
	this->speciesNode = speciesNode;
}

Genome::Genome(Genome * other) {
	this->loci = other->getLoci();
	this->genes = other->getGenome();
	this->speciesNode = other->getSpeciesNode();
}

Genome::Genome(Genome * other, bool randomize) {
	this->loci = other->getLoci();
	this->speciesNode = other->getSpeciesNode();
	if (randomize) {
		this->generateRandomGenes();
	} else {
		this->genes = other->getGenome();
	}
}

Genome::Genome(Genome * other, unsigned int rawGenes[]) {
	this->loci = other->getLoci();
	this->speciesNode = other->getSpeciesNode();
	vector<unsigned int> genes(rawGenes, rawGenes + loci.size());
	for (unsigned int i = 0; i < genes.size(); i++)
		if (this->loci[i]->outOfRange(genes[i]))
			throw ValueOutOfRangeException();
	this->genes = genes;
}

Genome::~Genome() {}

void Genome::generateRandomGenes() {
	genes.clear();
	for (unsigned int i = 0; i < loci.size(); i++)
		genes.push_back(loci[i]->randomIndex());
}

vector<unsigned int> Genome::getGenome() {
	return this->genes;
}

unsigned int Genome::genomeLength() {
	return this->genes.size();
}

vector<Locus*> Genome::getLoci() {
	return loci;
}

std::string Genome::getSpeciesNode() {
	return this->speciesNode;
}

int Genome::difference(Genome * otherGenome) {
	vector<unsigned int> otherGenes = otherGenome->getGenome();
	int difference = 0;
	unsigned int shorterGenome = fmin(
		this->genes.size(),
		otherGenes.size()
	);
	unsigned int longerGenome = fmax(
		this->genes.size(),
		otherGenes.size()
	);

	for (unsigned int i = 0; i < shorterGenome; i++)
		difference += abs(this->genes[i] - otherGenes[i]);

	// We want to account for genes of different lengths somehow
	if (longerGenome != shorterGenome)
		difference += longerGenome - shorterGenome;

	return difference;
}

string Genome::flatten() {
	stringstream ss;

	for (unsigned int i = 0; i < this->genes.size(); i++)
		ss << this->loci[i]->flatten(this->genes[i]) << " ";

	return ss.str();
}

Genome Genome::flattenGenome(Genome * target, bool exclude) {
	vector<unsigned int> rawGenome;
	vector<Locus*> rawLoci;

	for (unsigned int i = 0; i < this->genomeLength(); i++) {
		Locus * tempLocus = this->loci[i];
		if (!tempLocus->isConstructive()) {
			rawGenome.push_back(this->genes[i]);
			rawLoci.push_back(this->loci[i]);
		} else {
			Genome * temp = ((PopulationLocus*)tempLocus)->getIndex(
				this->genes[i]
			);

			if (temp == target) {
				if (!exclude) {
					rawGenome.push_back(this->genes[i]);
					rawLoci.push_back(this->loci[i]);
				}
			} else {
				Genome tempFlattened = temp->flattenGenome();
				vector<unsigned int> tempGenome =
					tempFlattened.getGenome();
				vector<Locus*> tempLoci =
					tempFlattened.getLoci();

				for (
					unsigned int k = 0;
					k < tempGenome.size();
					k++
				) {
					rawGenome.push_back(tempGenome[k]);
					rawLoci.push_back(tempLoci[k]);
				}
			}
		}
	}

	return Genome(rawGenome, rawLoci, this->speciesNode);
}

Genome Genome::flattenGenome() {
	return this->flattenGenome(NULL, false);
}

Genome Genome::flattenExceptFor(Genome * target) {
	return this->flattenGenome(target, false);
}

Genome Genome::flattenWithout(Genome * target) {
	return this->flattenGenome(target, true);
}

unsigned int Genome::getFlattenedIndex(Genome * target) {
	Genome temp = this->flattenGenome(target, false);
	vector<Locus*> tempLoci = temp.getLoci();

	// TODO: Make this a bit less hack-y
	for (unsigned int i = 0; i < temp.genomeLength(); i++)
		if (tempLoci[i]->isConstructive()) return i;

	throw ComponentNotPresentException(); 
}

bool Genome::usesComponent(Genome * component) {
	for (unsigned int i = 0; i < this->loci.size(); i++) {
		Locus * locus = this->loci[i];
		if (locus->isConstructive()) {
			Genome * temp = ((PopulationLocus*)locus)->getIndex(
				this->genes[i]
			);

			if (temp == component || temp->usesComponent(component))
				return true;
		}
	}

	return false;
}

set<Locus*> Genome::getConstructiveLoci() {
	set<Locus*> constructiveLoci;
	for (unsigned int i = 0; i < this->loci.size(); i++)
		if (this->loci[i]->isConstructive())
			constructiveLoci.insert(this->loci[i]);

	return constructiveLoci;
}

template <>
Genome * Genome::getIndex<Genome*>(unsigned int index) {
	return ((PopulationLocus*)this->loci[index])
		->getIndex(this->genes[index]);
}
