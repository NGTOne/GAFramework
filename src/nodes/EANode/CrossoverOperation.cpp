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
	for (int i = 1; i <= numParents; i++) numerator *= i;
	unsigned int denominator = 1;
	for (int i = 1; i <= (numParents - pairingSize); i++) denominator *= i;
	unsigned int maxPairings = numerator/denominator;
	return maxPairings;
}

// TODO: Refactor to make this work for n parents
vector<int> CrossoverOperation::getParents(
	int numAvailableParents,
	int desiredParents,
	vector<vector<int>> & previousPairings
) {
	uniform_int_distribution<int> parentDist(0, numAvailableParents - 1);
	vector<int> pairing;

	bool alreadySeen = false;
	int parent;
	do {
		for (int i = 0; i < desiredParents; i++) {
			do {
				parent = parentDist(this->generator);
			} while (find(
				pairing.begin(), pairing.end(), parent
			) != pairing.end());
			pairing.push_back(parent);
		}

		alreadySeen = true;
		for (int i = 0; i < previousPairings.size(); i++) {
			for (int k = 0; k < pairing.size(); k++)
				if (pairing[k] != previousPairings[i][k])
					alreadySeen = false;
		}
	} while (alreadySeen == true);

	previousPairings.push_back(pairing);
	return pairing;
}

vector<vector<int>> CrossoverOperation::getGenomes(vector<Genome*> parents) {
	vector<vector<int>> parentGenomes;
	for (int i = 0; i < parents.size(); i++)
		parentGenomes.push_back(parents[i]->getGenome());
	return parentGenomes;
}

vector<vector<Locus*>> CrossoverOperation::getLoci(vector<Genome*> parents) {
	vector<vector<Locus*>> parentLoci;
	for (int i = 0; i < parents.size(); i++)
		parentLoci.push_back(parents[i]->getLoci());
	return parentLoci;
}

unsigned int CrossoverOperation::shortestGenome(vector<Genome*> genomes) {
	unsigned int shortestGenomeLength = 0;

	for (unsigned int i = 0; i < genomes.size(); i++) {
		if (genomes[i]->genomeLength() < shortestGenomeLength
			|| shortestGenomeLength == 0
		) {
			shortestGenomeLength = genomes[i]->genomeLength();
		}
	}

	return shortestGenomeLength;
}
