#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "crossovers/NPointCrossover.hpp"

// TEMP
#include <iostream>

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

vector<unsigned int> NPointCrossover::getPoints(unsigned int maxPoint) {
	vector<unsigned int> points;
	uniform_int_distribution<unsigned int> pointsDist(0, maxPoint);

	for (unsigned int i = 0; i < this->numPoints; i++) 
		points.push_back(pointsDist(this->generator));

	sort(points.begin(), points.begin() + this->numPoints);

	// Remove duplicate points
	for (unsigned int i = 1; i < points.size(); i++)
		if (points[i] == points[i-1])
			points.erase(points.begin() + i--);

	return points;
}

std::vector<std::tuple<
	std::vector<unsigned int>,
	std::vector<Locus*>
>> NPointCrossover::crossOver(std::vector<Genome*> genomes) {
	unsigned int shortestGenomeLength = this->shortestGenome(genomes);
	vector<unsigned int> points = this->getPoints(shortestGenomeLength);
	unsigned int currentPoint = 0, currentParent = 0;
	vector<vector<unsigned int>> childGenomes(
		genomes.size(),
		vector<unsigned int>()
	);
	vector<vector<unsigned int>> parentGenomes = this->getGenomes(genomes);
	vector<vector<Locus*>> childLoci(genomes.size(), vector<Locus*>());
	vector<vector<Locus*>> parentLoci = this->getLoci(genomes);

	for (unsigned int i = 0; i < shortestGenomeLength; i++) {
		if (currentPoint < points.size() && i == points[currentPoint]) {
			if (currentParent++ == genomes.size() - 1)
				currentParent = 0;
			currentPoint++;
		}

		for (unsigned int k = 0; k < childGenomes.size(); k++) {
			unsigned int parent = currentParent + k;
			if (parent >= genomes.size()) parent -= genomes.size();

			childGenomes[k].push_back(parentGenomes[parent][i]);
			childLoci[k].push_back(parentLoci[parent][i]);
		}
	}

	std::vector<std::tuple<
		std::vector<unsigned int>,
		std::vector<Locus*>
	>> children;

	for (unsigned int i = 0; i < childGenomes.size(); i++)
		children.push_back(
			std::make_tuple(childGenomes[i], childLoci[i])
		);

	if (children.size() > this->numOffspring) {
		unsigned int numToDelete = children.size() - numOffspring;
		for (unsigned int i = 0; i < numToDelete; i++) {
			uniform_int_distribution<unsigned int> removalDist(
				0,
				children.size()
			);

			unsigned int index = removalDist(this->generator);
			children.erase(children.begin() + index);
		}
	}

	return children;
}

string NPointCrossover::toString() {
	stringstream ss;

	ss << "Type: N-Point Crossover\nRandom Seed: " << this->seed
		<< "\nNumber of points: " << this->numPoints << "\n";

	return ss.str();
}
