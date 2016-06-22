//This is an abstract class for crossover operations. Lets us define any 
//crossover we like, and use it for a given Individual.

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <algorithm>
#include "nodes/EANode/CrossoverOperation.hpp"
using namespace std;

CrossoverOperation::CrossoverOperation() {
	init(
		DEFAULT_NUM_OFFSPRING,
		chrono::system_clock::now().time_since_epoch().count()
	);
}

CrossoverOperation::CrossoverOperation(unsigned int numOffspring) {
	init(
		numOffspring,
		chrono::system_clock::now().time_since_epoch().count()
	);
}

CrossoverOperation::CrossoverOperation(
	unsigned int numOffspring,
	unsigned seed
) {
	init(numOffspring, seed);
}

CrossoverOperation::~CrossoverOperation() {}

void CrossoverOperation::init(unsigned int numOffspring, unsigned seed) {
	this->numOffspring = numOffspring;
	this->seed = seed;
	generator = mt19937(seed);
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
	uniform_int_distribution<unsigned int> parentDist(
		0,
		numAvailableParents - 1
	);
	vector<unsigned int> pairing;

	bool alreadySeen = false;
	unsigned int parent;
	do {
		for (unsigned int i = 0; i < desiredParents; i++) {
			do {
				parent = parentDist(this->generator);
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

vector<vector<unsigned int>> CrossoverOperation::getGenomes(
	vector<Genome*> parents
) {
	vector<vector<unsigned int>> parentGenomes;
	for (unsigned int i = 0; i < parents.size(); i++)
		parentGenomes.push_back(parents[i]->getGenome());
	return parentGenomes;
}

vector<vector<Locus*>> CrossoverOperation::getLoci(vector<Genome*> parents) {
	vector<vector<Locus*>> parentLoci;
	for (unsigned int i = 0; i < parents.size(); i++)
		parentLoci.push_back(parents[i]->getLoci());
	return parentLoci;
}

std::vector<Genome*> CrossoverOperation::crossOver(
	std::vector<Genome*> parents,
	std::string speciesNode
) {
	std::vector<std::tuple<
		std::vector<unsigned int>,
		std::vector<Locus*>
	>> genomeTemplates = this->crossOver(parents);
	std::vector<Genome *> offspring;

	for (unsigned int i = 0; i < genomeTemplates.size(); i++)
		offspring.push_back(
			new Genome(genomeTemplates[i], speciesNode)
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
