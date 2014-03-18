#include <cstdlib>
#include <random>
#include <chrono>
#include "GenePool.h"

using namespace std;

GenePool::GenePool() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(seed);
}

GenePool::GenePool(unsigned overriddenSeed) {
	init(overriddenSeed);
}

void GenePool::init(unsigned newSeed) {
	mt19937 newGenerator(newSeed);
	generator = newGenerator;
}

int GenePool::getPopulationSize() {
	return populationSize;
}

int GenePool::chooseRandomMember() {
	uniform_int_distribution<int> selectionDistribution(0, populationSize-1);

	int randomMember = selectionDistribution(generator);

	printf("%d", randomMember);

	return randomMember;
}

int GenePool::getSeed() {
	return seed;
}

bool GenePool::equals(GenePool * otherPool) {
	if (seed == otherPool->getSeed() && populationSize == otherPool->getPopulationSize()) {
		return true;
	} else {
		return false;
	}
}
