#include <random>
#include <chrono>
#include <sstream>
#include "crossovers/CutAndSpliceCrossover.hpp"

using namespace std;

CutAndSpliceCrossover::CutAndSpliceCrossover() : CrossoverOperation() {}

CutAndSpliceCrossover::CutAndSpliceCrossover(unsigned newSeed) : CrossoverOperation(newSeed) {}

Genome ** CutAndSpliceCrossover::crossOver(Genome * firstGenome, Genome * secondGenome) {
	int shortestGenome;

	int firstGenomeLength = firstGenome->getGenomeLength();
	int secondGenomeLength = secondGenome->getGenomeLength();

	int * genomeOne = firstGenome->getGenome();
	int * genomeTwo = secondGenome->getGenome();

	GeneNode ** firstGeneNodes = firstGenome->getGeneNodes();
	GeneNode ** secondGeneNodes = secondGenome->getGeneNodes();

	if (firstGenomeLength > secondGenomeLength) {
		shortestGenome = secondGenomeLength;
	} else {
		shortestGenome = firstGenomeLength;
	}

	uniform_int_distribution<int> pointDistribution(0, shortestGenome);

	//We're generating two children - each one uses the same crossover
	//points, but draws from the parents in a different order
	int ** children = (int**)malloc(sizeof(int*)*2);

	int firstSplicePoint = pointDistribution(generator);
	int secondSplicePoint = pointDistribution(generator);

	int firstChildLength = firstSplicePoint+(secondGenomeLength-secondSplicePoint);
	int secondChildLength = secondSplicePoint+(firstGenomeLength-firstSplicePoint);

	children[0] = (int*)malloc(sizeof(int)*firstChildLength);
	children[1] = (int*)malloc(sizeof(int)*secondChildLength);

	GeneNode *** childPools = (GeneNode***)malloc(sizeof(GeneNode**)*2);

	childPools[0] = (GeneNode**)malloc(sizeof(GeneNode*)*firstChildLength);
	childPools[1] = (GeneNode**)malloc(sizeof(GeneNode*)*secondChildLength);

	//Create the first child
	for (int i = 0; i < firstChildLength; i++) {
		if (i < firstSplicePoint) {
			children[0][i] = genomeOne[i];
			childPools[0][i] = firstGeneNodes[i];
		} else {
			for (int k = 0; k+i < firstChildLength; k++) {
				children[0][k+i] = genomeTwo[secondSplicePoint+k];
				childPools[0][k+i] = secondGeneNodes[secondSplicePoint+k];
			}

			i = firstChildLength;
		}
	}

	for (int i = 0; i < secondChildLength; i++) {
		if (i < secondSplicePoint) {
			children[1][i] = genomeTwo[i];
			childPools[1][i] = secondGeneNodes[i];
		} else {
			for (int k = 0; k+i < secondChildLength; k++) {
				children[1][k+i] = genomeOne[firstSplicePoint+k];
				childPools[1][k+i] = firstGeneNodes[firstSplicePoint+k];
			}
		}
	}

	Genome ** returnChildren = (Genome**)malloc(sizeof(Genome*)*2);

	returnChildren[0] = new Genome(children[0], firstChildLength, childPools[0]);
	returnChildren[1] = new Genome(children[1], secondChildLength, childPools[1]);

	free(children[0]);
	free(children[1]);
	free(children);

	return returnChildren;
}

string CutAndSpliceCrossover::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Type: Cut and Splice Crossover\nRandom Seed: " << seed << "\n";

	returnString = ss.str();

	return returnString;
}
