#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "nodes/EANode/crossovers/NPointCrossover.hpp"
#include "core/utils/HierRNG.hpp"

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

std::vector<unsigned int> NPointCrossover::getPoints(unsigned int maxPoint) {
	std::vector<unsigned int> points;

	for (unsigned int i = 0; i < this->numPoints; i++) 
		points.push_back(HierRNG::index(maxPoint));

	std::sort(points.begin(), points.begin() + this->numPoints);

	// Remove duplicate points
	for (unsigned int i = 1; i < points.size(); i++)
		if (points[i] == points[i-1])
			points.erase(points.begin() + i--);

	return points;
}

// TODO: Refactor this
std::vector<GenomeTemplate> NPointCrossover::crossOver(
	std::vector<GenomeTemplate> parents
) {
	unsigned int shortestGenomeLength = this->shortestGenome(parents);
	std::vector<unsigned int> points =
		this->getPoints(shortestGenomeLength);
	unsigned int currentPoint = 0, currentParent = 0;
	std::vector<GenomeTemplate> children(parents.size(), GenomeTemplate());

	for (unsigned int i = 0; i < shortestGenomeLength; i++) {
		if (
			currentPoint < points.size()
			&& i == points[currentPoint]
		) {
			if (currentParent++ == parents.size() - 1)
				currentParent = 0;
			currentPoint++;
		}

		for (unsigned int k = 0; k < children.size(); k++) {
			unsigned int parent = currentParent + k;
			if (parent >= parents.size()) parent -= parents.size();
			children[k].add(parents[parent].getGene(i));
		}
	}

	if (children.size() > this->numOffspring) {
		unsigned int numToDelete = children.size() - numOffspring;
		for (unsigned int i = 0; i < numToDelete; i++)
			children.erase(
				children.begin()
					+ HierRNG::index(children.size() - 1)
			);
	}

	return children;
}

std::string NPointCrossover::toString() {
	std::stringstream ss;

	ss << "Type: N-Point Crossover"
		<< "\nNumber of points: " << this->numPoints << "\n";

	return ss.str();
}
