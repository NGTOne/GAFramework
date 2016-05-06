#include "core/Solution.hpp"
#include "core/Genome.hpp"
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Solution::Solution() {
	init(NULL, NULL);
}

Solution::Solution(Genome * genome) {
	init(new Genome(genome, false), NULL);
	//evaluateFitness();
}

Solution::Solution(Solution * copyTarget, bool randomize) {
	Genome * genome = new Genome(copyTarget->getGenome(), randomize);
	if (randomize) {
		init(genome, NULL);
		//evaluateFitness();
	} else {
		init(genome, copyTarget->getProperties());
	}
}

Solution::Solution(Solution * copyTarget, int rawGenes[]) {
	Genome * genome = new Genome(copyTarget->getGenome(), rawGenes);
	init(genome, NULL);
	//evaluateFitness();
}

Solution::Solution(vector<Locus*> loci) {
	Genome * genome = new Genome(loci);
	init(genome, NULL);
	//evaluateFitness();
}

Solution::~Solution() {
	if (genome != NULL) {
		delete(genome);
	}

	if (properties != NULL) {
		delete(properties);
	}
}

void Solution::init(Genome * genome, PropertiesList * properties) {
	this->genome = genome;
	this->properties = properties;
}

int Solution::getFitness() {
	return this->properties->getFitness();
}

PropertiesList * Solution::getProperties() {
	return this->properties;
}

Genome * Solution::getGenome() {
	return this->genome;
}

/*string Solution::toString() {
	return this->toString->toString(this->genome);
}*/
