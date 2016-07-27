#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "nodes/EANode/crossovers/NPointCrossover.hpp"
#include "core/HierRNG.hpp"

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

vector<unsigned int> NPointCrossover::getPoints(unsigned int maxPoint) {
	vector<unsigned int> points;

	for (unsigned int i = 0; i < this->numPoints; i++) 
		points.push_back(HierRNG::index(maxPoint));

	sort(points.begin(), points.begin() + this->numPoints);

	// Remove duplicate points
	for (unsigned int i = 1; i < points.size(); i++)
		if (points[i] == points[i-1])
			points.erase(points.begin() + i--);

	return points;
}

// TODO: Refactor this
std::vector<GenomeTemplate> NPointCrossover::crossOver(
	std::vector<Genome*> genomes
) {
	unsigned int shortestGenomeLength = this->shortestGenome(genomes);
	vector<unsigned int> points = this->getPoints(shortestGenomeLength);
	unsigned int currentPoint = 0, currentParent = 0;
	std::vector<GenomeTemplate> children(genomes.size(), GenomeTemplate());
	std::vector<GenomeTemplate> parents = this->getTemplates(genomes);

	for (unsigned int i = 0; i < shortestGenomeLength; i++) {
		if (
			currentPoint < points.size()
			&& i == points[currentPoint]
		) {
			if (currentParent++ == genomes.size() - 1)
				currentParent = 0;
			currentPoint++;
		}

		for (unsigned int k = 0; k < children.size(); k++) {
			unsigned int parent = currentParent + k;
			if (parent >= genomes.size()) parent -= genomes.size();
			children[k].add(parents[parent].getIndex(i));
		}
	}

	if (children.size() > this->numOffspring) {
		unsigned int numToDelete = children.size() - numOffspring;
		for (unsigned int i = 0; i < numToDelete; i++) {
			unsigned int index = HierRNG::index(children.size()-1);
			children.erase(children.begin() + index);
		}
	}

	return children;
}

string NPointCrossover::toString() {
	stringstream ss;

	ss << "Type: N-Point Crossover"
		<< "\nNumber of points: " << this->numPoints << "\n";

	return ss.str();
}
