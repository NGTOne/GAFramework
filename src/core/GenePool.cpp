#include <cstdlib>
#include <random>
#include <chrono>
#include "GenePool.h"

using namespace std;

GenePool::GenePool() {
	seed = chrono::system_clock::now().time_since_epoch().count();
}

GenePool::GenePool(unsigned overriddenSeed) : seed(overriddenSeed) {}

int GenePool::getPopulationSize() {
	return populationSize;
}

int GenePool::chooseRandomMember() {
	mt19937 generator(seed);
	uniform_int_distribution<int> selectionDistribution(0, populationSize-1);

	int randomMember = selectionDistribution(generator);

	return randomMember;
}

int GenePool::getSeed() {
	return seed;
}

bool GenePool::equals(GenePool otherPool) {
	if (seed == otherPool.getSeed() && populationSize == otherPool.getPopulationSize()) {
		return true;
	} else {
		return false;
	}
}
