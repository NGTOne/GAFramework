#include "instruments/population/GenerationHammingDistanceCSV.hpp"
#include <string>

GenerationHammingDistanceCSV::GenerationHammingDistanceCSV(
	PopulationNode* target,
	std::string outFile,
	std::vector<std::string> targetString
) : GenerationalCSVInstrument(target, outFile) {
	this->targetString = targetString;

	std::vector<unsigned int> header(targetString.size() + 1);
	std::iota(header.begin(), header.end(), 0);

	this->addToHeader("Generation");
	this->addToHeader(header);
}

unsigned int GenerationHammingDistanceCSV::checkHammingDistance(
	Genome* target
) {
	unsigned int distance = 0;
	std::vector<Gene*> genes = target->getGenome();
	for (unsigned int i = 0; i < genes.size(); i++)
		if (genes[i]->flatten() != this->targetString[i]) distance++;
	return distance;
}

void GenerationHammingDistanceCSV::report() {
	std::vector<unsigned int> distances(this->targetString.size() + 1);
	std::iota(distances.begin(), distances.end(), 0);
	auto output = this->buildEmptyMap(distances, (unsigned int)0);
	output.emplace("Generation", this->target->currentGeneration());

	for (unsigned int i = 0; i < this->target->populationSize(); i++)
		output[std::to_string(
			this->checkHammingDistance(this->target->getIndex(i))
		)]++;
	this->write(output, (unsigned int)0);
}
