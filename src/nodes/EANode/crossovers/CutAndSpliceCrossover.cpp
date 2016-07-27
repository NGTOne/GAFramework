#include <random>
#include <sstream>
#include <algorithm>
#include "nodes/EANode/crossovers/CutAndSpliceCrossover.hpp"
#include "core/HierRNG.hpp"

using namespace std;

CutAndSpliceCrossover::CutAndSpliceCrossover() : CrossoverOperation() {}

GenomeTemplate CutAndSpliceCrossover::createOffspring(
	vector<Genome*> parents,
	vector<unsigned int> points
) {
	GenomeTemplate offspring;
	std::vector<GenomeTemplate> templates = this->getTemplates(parents);

	unsigned int offspringGenomeLength = points[0] +
		(parents[1]->genomeLength() - points[1]);

	for (unsigned int i = 0; i < offspringGenomeLength; i++) {
		if (i < points[0]) {
			offspring.add(templates[0].getIndex(i));
		} else {
			offspring.add(
				templates[1].getIndex(
					points[1] + (i - points[0])
				)
			);
		}
	}

	return offspring;
}

std::vector<GenomeTemplate> CutAndSpliceCrossover::crossOver(
	std::vector<Genome*> genomes
) {
	vector<unsigned int> genomeLengths, points;
	std::vector<GenomeTemplate> offspring;
	vector<vector<unsigned int>> pairings;

	for (unsigned int i = 0; i < genomes.size(); i++) {
		genomeLengths.push_back(genomes[i]->genomeLength());
		points.push_back(HierRNG::uniformRandomNumber<
			unsigned int
		>(0, genomeLengths[i]));
	}

	unsigned int numPairings = this->maxPairings(genomes.size(), 2);
	vector<unsigned int> parentIndexes;
	for (unsigned int i = 0; i < numPairings; i++) {
		parentIndexes = this->getParents(genomes.size(), 2, pairings);
		vector<Genome*> parents;
		vector<unsigned int> parentPoints;
		for (int k = 0; k < 2; k++) {
			parents.push_back(genomes[parentIndexes[k]]);
			parentPoints.push_back(points[parentIndexes[k]]);
		}

		offspring.push_back(
			this->createOffspring(parents, parentPoints)
		);
	}

	return offspring;
}

string CutAndSpliceCrossover::toString() {
	stringstream ss;
	ss << "Type: Cut and Splice Crossover\n";
	return ss.str();
}
