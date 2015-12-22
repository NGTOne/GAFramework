#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "crossovers/NPointCrossover.hpp"

using namespace std;

NPointCrossover::NPointCrossover(int newNumPoints) : CrossoverOperation() {
	numPoints = newNumPoints;
}

NPointCrossover::NPointCrossover(int newNumPoints, unsigned newSeed) : CrossoverOperation(newSeed) {
	numPoints = newNumPoints;
}

Genome ** NPointCrossover::crossOver(Genome * firstGenome, Genome * secondGenome) {
	int points[numPoints];
	int shortestGenome;

	int firstGenomeLength = firstGenome->getGenomeLength();
	int secondGenomeLength = secondGenome->getGenomeLength();

	int * genomeOne = firstGenome->getGenome();
	int * genomeTwo = secondGenome->getGenome();

	if (firstGenomeLength > secondGenomeLength) {
		shortestGenome = secondGenomeLength;
	} else {
		shortestGenome = firstGenomeLength;
	}

	//We're generating two children - each one sees the same crossover
	//points, but draws from the parents in a different order
	int ** children = (int**)malloc(sizeof(int*)*2);

	children[0] = (int*)malloc(sizeof(int)*shortestGenome);
	children[1] = (int*)malloc(sizeof(int)*shortestGenome);

	uniform_int_distribution<int> distribution(0, firstGenomeLength);

	//Generate the points - duplicates will be taken care of later
	for (int i = 0; i < numPoints; i++) {
		points[i] = distribution(generator);
	}

	//Sort the points
	sort(points, points+numPoints);

	//Replace the duplicate points with -1 (which would never appear as a
	//valid point)
	for (int i = 0; i < numPoints-1; i++) {
		if (points[i+1] == points[i]) {
			for (int k = i+1; k < numPoints && points[k] == points[i]; k++) {
				points[k] = -1;
			}
		}
	}

	int currentPoint = 0;
	bool firstOrSecond = false; //false = first, true = second

	for (int i = 0; i < shortestGenome; i++) {
		if (currentPoint < numPoints) {
			if (i == points[currentPoint]) {
				firstOrSecond = !firstOrSecond;
				currentPoint += 1;
			} else {
				for (; currentPoint < numPoints && points[currentPoint] == -1; currentPoint++);
			}
		}

		if (firstOrSecond == true) {
			children[0][i] = genomeOne[i];
			children[1][i] = genomeTwo[i];
		} else {
			children[1][i] = genomeOne[i];
			children[0][i] = genomeTwo[i];
		}
	}

	Genome ** returnChildren = (Genome**)malloc(sizeof(Genome*)*2);

	returnChildren[0] = new Genome(children[0], shortestGenome, firstGenome->getGeneNodes());
	returnChildren[1] = new Genome(children[1], shortestGenome, secondGenome->getGeneNodes());

	free(children[0]);
	free(children[1]);
	free(children);

	return returnChildren;
}

string NPointCrossover::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Type: N-Point Crossover\nRandom Seed: " << seed << "\nNumber of points: " << numPoints << "\n";

	returnString = ss.str();

	return returnString;
}
