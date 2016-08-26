#include "nodes/EANode/crossovers/BlendedCrossover.hpp"
#include "exception/MismatchedCountsException.hpp"
#include <limits>
#include <sstream>

BlendedCrossover::BlendedCrossover(
	std::vector<double> parentWeights
) : CrossoverOperation(1) {
	this->parentWeights = parentWeights;
}

std::vector<GenomeTemplate> BlendedCrossover::crossOver(
	std::vector<GenomeTemplate> parents
) {
	if (this->parentWeights.empty())
		this->parentWeights = std::vector<double>(
			parents.size(),
			1.0/parents.size()
		);

	if (this->parentWeights.size() != parents.size())
		throw MismatchedCountsException("Number of parent weights must be the same as the number of parents!");

	std::vector<std::vector<Gene*>> rawGenes;
	std::vector<Gene*> result;
	double avgIndex;
	unsigned int shortestGenome = this->shortestGenome(parents);

	for (unsigned int i = 0; i < parents.size(); i++)
		rawGenes.push_back(parents[i].getGenes());

	for (unsigned int i = 0; i < shortestGenome; i++) {
		avgIndex = 0;
		for (unsigned int k = 0; k < rawGenes.size(); k++)
			avgIndex += rawGenes[k][i]->getIndex() *
				this->parentWeights[k];

		result.push_back(rawGenes[0][i]->copy(avgIndex));
	}

	return {GenomeTemplate(result)};
}

std::string BlendedCrossover::toString() {
	std::stringstream ss;
	ss << "Type: Blended Crossover\n";
	return ss.str();
}
