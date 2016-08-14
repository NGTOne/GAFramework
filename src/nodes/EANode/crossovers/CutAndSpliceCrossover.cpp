#include <random>
#include <sstream>
#include <algorithm>
#include "nodes/EANode/crossovers/CutAndSpliceCrossover.hpp"
#include "core/utils/HierRNG.hpp"

CutAndSpliceCrossover::CutAndSpliceCrossover() : CrossoverOperation() {}

GenomeTemplate CutAndSpliceCrossover::createOffspring(
	std::vector<GenomeTemplate> parents,
	std::vector<unsigned int> points
) {
	GenomeTemplate offspring;

	unsigned int offspringGenomeLength =
		points[0] + (parents[1].genomeLength() - points[1]);

	for (unsigned int i = 0; i < offspringGenomeLength; i++) {
		if (i < points[0]) {
			offspring.add(parents[0].getGene(i));
		} else {
			offspring.add(parents[1].getGene(
				points[1] + (i - points[0])
			));
		}
	}

	return offspring;
}

std::vector<GenomeTemplate> CutAndSpliceCrossover::crossOver(
	std::vector<GenomeTemplate> parents
) {
	std::vector<unsigned int> genomeLengths, points;
	std::vector<GenomeTemplate> offspring;
	std::vector<std::vector<unsigned int>> pairings;

	for (unsigned int i = 0; i < parents.size(); i++) {
		genomeLengths.push_back(parents[i].genomeLength());
		points.push_back(HierRNG::index(genomeLengths[i]));
	}

	unsigned int numPairings = this->maxPairings(parents.size(), 2);
	std::vector<unsigned int> parentIndices;
	for (unsigned int i = 0; i < numPairings; i++) {
		parentIndices = this->getParents(parents.size(), 2, pairings);
		std::vector<GenomeTemplate> currentParents;
		std::vector<unsigned int> parentPoints;
		for (unsigned int k = 0; k < 2; k++) {
			currentParents.push_back(parents[parentIndices[k]]);
			parentPoints.push_back(points[parentIndices[k]]);
		}

		offspring.push_back(
			this->createOffspring(currentParents, parentPoints)
		);
	}

	return offspring;
}

std::string CutAndSpliceCrossover::toString() {
	std::stringstream ss;
	ss << "Type: Cut and Splice Crossover\n";
	return ss.str();
}
