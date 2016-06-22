#include <random>
#include <sstream>
#include <algorithm>
#include "crossovers/CutAndSpliceCrossover.hpp"

using namespace std;

CutAndSpliceCrossover::CutAndSpliceCrossover() : CrossoverOperation() {}

CutAndSpliceCrossover::CutAndSpliceCrossover(
	unsigned seed
) : CrossoverOperation(seed) {}

std::tuple<
	std::vector<unsigned int>,
	std::vector<Locus*>
> CutAndSpliceCrossover::createOffspring(
	vector<Genome*> parents,
	vector<unsigned int> points
) {
	vector<unsigned int> offspringGenome;
	vector<Locus*> offspringLoci;
	vector<vector<unsigned int>> parentGenomes = this->getGenomes(parents);
	vector<vector<Locus*>> parentLoci = this->getLoci(parents);

	unsigned int offspringGenomeLength = points[0] +
		(parents[1]->genomeLength() - points[1]);

	for (unsigned int i = 0; i < offspringGenomeLength; i++) {
		if (i < points[0]) {
			offspringGenome.push_back(parentGenomes[0][i]);
			offspringLoci.push_back(parentLoci[0][i]);
		} else {
			offspringGenome.push_back(
				parentGenomes[1][points[1] + (i - points[0])]
			);
			offspringLoci.push_back(
				parentLoci[1][points[1] + (i - points[0])]
			);
		}
	}

	return std::make_tuple(offspringGenome, offspringLoci);
}

std::vector<std::tuple<
	std::vector<unsigned int>,
	std::vector<Locus*>
>> CutAndSpliceCrossover::crossOver(vector<Genome*> genomes) {
	vector<unsigned int> genomeLengths, points;
	std::vector<std::tuple<
		std::vector<unsigned int>,
		std::vector<Locus*>
	>> offspring;
	vector<vector<unsigned int>> pairings;

	for (unsigned int i = 0; i < genomes.size(); i++) {
		genomeLengths.push_back(genomes[i]->genomeLength());
		uniform_int_distribution<int> pointDist(0, genomeLengths[i]);
		points.push_back(pointDist(this->generator));
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
	string returnString = "";
	stringstream ss;

	ss << "Type: Cut and Splice Crossover\nRandom Seed: " << seed << "\n";

	returnString = ss.str();

	return returnString;
}
