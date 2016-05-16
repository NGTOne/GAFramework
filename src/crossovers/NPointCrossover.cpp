#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "crossovers/NPointCrossover.hpp"

using namespace std;

NPointCrossover::NPointCrossover (
	unsigned int numPoints
) : CrossoverOperation() {
	this->numPoints = numPoints;
}

NPointCrossover::NPointCrossover(
	unsigned int numPoints,
	unsigned int numOffspring
) : CrossoverOperation(numOffspring) {
	this->numPoints = numPoints;
}

NPointCrossover::NPointCrossover(
	unsigned int numPoints,
	unsigned int numOffspring,
	unsigned seed
) : CrossoverOperation(numOffspring, seed) {
	this->numPoints = numPoints;
}

vector<int> NPointCrossover::getPoints(int maxPoint) {
	vector<int> points;
	uniform_int_distribution<int> pointsDist(0, maxPoint);

	for (int i = 0; i < this->numPoints; i++) {
		points.push_back(pointsDist(this->generator));
	}

	sort(points.begin(), points.begin() + this->numPoints);
	return points;
}

vector<Genome*> NPointCrossover::crossOver(std::vector<Genome*> genomes) {
	int shortestGenomeLength = this->shortestGenome(genomes);

	vector<int> points = this->getPoints(shortestGenomeLength);
	int currentPoint = 0, currentParent = 0;
	vector<vector<int>> childGenomes;
	childGenomes.resize(genomes.size());
	vector<vector<int>> parentGenomes = this->getGenomes(genomes);
	vector<vector<Locus*>> childLoci;
	childLoci.resize(genomes.size());
	vector<vector<Locus*>> parentLoci = this->getLoci(genomes);

	for (int i = 0; i < shortestGenomeLength; i++) {
		if (i == points[currentPoint]) {
			currentParent = (currentParent == genomes.size() - 1)
				? 0 : currentParent++;
			do currentPoint++; while (
				points[currentPoint] ==
				points[currentPoint - 1]
			);
		}

		for (int k = 0; k < childGenomes.size(); k++) {
			int parent = currentParent + k;
			if (parent >= genomes.size()) parent -= genomes.size();

			childGenomes[k].push_back(parentGenomes[parent][i]);
			childLoci[k].push_back(parentLoci[parent][i]);
		}
	}

	vector<Genome*> children;

	for (int i = 0; i < childGenomes.size(); i++) {
		children.push_back(new Genome(childGenomes[i], childLoci[i]));
	}

	if (children.size() > this->numOffspring) {
		int numToDelete = children.size() - numOffspring;
		for (int i = 0; i < numToDelete; i++) {
			uniform_int_distribution<int> removalDist(
				0,
				children.size()
			);

			int index = removalDist(this->generator);

			children.erase(children.begin() + index);
		}
	}

	return children;
}

string NPointCrossover::toString() {
	stringstream ss;

	ss << "Type: N-Point Crossover\nRandom Seed: " << seed << "\nNumber of points: " << numPoints << "\n";

	return ss.str();
}
