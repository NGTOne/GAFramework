#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <algorithm>
#include "nodes/EANode/CrossoverOperation.hpp"
#include "core/HierRNG.hpp"
using namespace std;

CrossoverOperation::CrossoverOperation() {
	this->init(DEFAULT_NUM_OFFSPRING);
}

CrossoverOperation::CrossoverOperation(unsigned int numOffspring) {
	this->init(numOffspring);
}

CrossoverOperation::~CrossoverOperation() {}

void CrossoverOperation::registerInternalObjects(
	NodeGarbageCollector & collector
) {}

void CrossoverOperation::init(unsigned int numOffspring) {
	this->numOffspring = numOffspring;
}

unsigned int CrossoverOperation::maxPairings(
	unsigned int numParents,
	unsigned int pairingSize
) {
	unsigned int numerator = 1;
	for (unsigned int i = 1; i <= numParents; i++) numerator *= i;
	unsigned int denominator = 1;
	for (unsigned int i = 1; i <= (numParents - pairingSize); i++)
		denominator *= i;
	unsigned int maxPairings = numerator/denominator;
	return maxPairings;
}

// TODO: Refactor to make this work for n parents
vector<unsigned int> CrossoverOperation::getParents(
	unsigned int numAvailableParents,
	unsigned int desiredParents,
	vector<vector<unsigned int>> & previousPairings
) {
	vector<unsigned int> pairing;

	bool alreadySeen = false;
	unsigned int parent;
	do {
		for (unsigned int i = 0; i < desiredParents; i++) {
			do {
				parent = HierRNG::index(numAvailableParents-1);
			} while (find(
				pairing.begin(), pairing.end(), parent
			) != pairing.end());
			pairing.push_back(parent);
		}

		alreadySeen = true;
		for (unsigned int i = 0; i < previousPairings.size(); i++)
			for (unsigned int k = 0; k < pairing.size(); k++)
				if (pairing[k] != previousPairings[i][k])
					alreadySeen = false;
	} while (alreadySeen == true);

	previousPairings.push_back(pairing);
	return pairing;
}

std::vector<GenomeTemplate> CrossoverOperation::getTemplates(
	std::vector<Genome*> parents
) {
	std::vector<GenomeTemplate> templates;
	for (unsigned int i = 0; i < parents.size(); i++)
		templates.push_back(parents[i]->getTemplate());
	return templates;
}

std::vector<Genome*> CrossoverOperation::crossOver(
	std::vector<Genome*> parents,
	std::string speciesNode
) {
	std::vector<GenomeTemplate> templates = this->crossOver(parents);
	std::vector<Genome *> offspring;

	for (unsigned int i = 0; i < templates.size(); i++)
		offspring.push_back(
			new Genome(templates[i], speciesNode)
		);

	return offspring;
}

unsigned int CrossoverOperation::shortestGenome(vector<Genome*> genomes) {
	unsigned int shortestGenomeLength = 0;

	for (unsigned int i = 0; i < genomes.size(); i++)
		if (genomes[i]->genomeLength() < shortestGenomeLength
			|| shortestGenomeLength == 0)
			shortestGenomeLength = genomes[i]->genomeLength();

	return shortestGenomeLength;
}
