#include "nodes/EANode/crossovers/BlendedCrossover.hpp"
#include <limits>
#include <sstream>

BlendedCrossover::BlendedCrossover() : CrossoverOperation(1) {}

std::vector<GenomeTemplate> BlendedCrossover::crossOver(
	std::vector<GenomeTemplate> parents
) {
	std::vector<std::vector<Gene*>> rawGenes;
	std::vector<Gene*> result;
	double avgIndex;
	unsigned int shortestGenome = std::numeric_limits<unsigned int>::max();

	for (unsigned int i = 0; i < parents.size(); i++) {
		rawGenes.push_back(parents[i].getGenes());
		if (parents[i].genomeLength() < shortestGenome)
			shortestGenome = parents[i].genomeLength();
	}

	for (unsigned int i = 0; i < shortestGenome; i++) {
		avgIndex = 0;
		for (unsigned int k = 0; k < rawGenes.size(); k++)
			avgIndex += rawGenes[k][i]->getIndex();
		avgIndex /= rawGenes.size();

		result.push_back(rawGenes[0][i]->copy(avgIndex));
	}

	return {GenomeTemplate(result)};
}

std::string BlendedCrossover::toString() {
	std::stringstream ss;
	ss << "Type: Blended Crossover\n";
	return ss.str();
}
