#include <cstdlib>
#include <random>
#include <chrono>
#include "core/GeneNode.hpp"

using namespace std;

GeneNode::GeneNode() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(seed);
}

GeneNode::GeneNode(unsigned overriddenSeed) {
	init(overriddenSeed);
}

GeneNode::~GeneNode() {}

void GeneNode::init(unsigned newSeed) {
	seed = newSeed;
	mt19937 newGenerator(seed);
	generator = newGenerator;
}

int GeneNode::getPopulationSize() {
	return populationSize;
}

int GeneNode::chooseRandomMember() {
	uniform_int_distribution<int> selectionDistribution(0, populationSize-1);

	int randomMember = selectionDistribution(generator);

	return randomMember;
}

int GeneNode::getSeed() {
	return seed;
}

bool GeneNode::equals(GeneNode * otherPool) {
	if (seed == otherPool->getSeed() && populationSize == otherPool->getPopulationSize()) {
		return true;
	} else {
		return false;
	}
}
