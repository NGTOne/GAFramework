#include "instruments/population/GenerationHammingDistanceCSV.hpp"
#include <string>

GenerationHammingDistanceCSV::GenerationHammingDistanceCSV(
	PopulationNode* target,
	std::string outFile,
	std::vector<std::string> targetString
) : CSVInstrument(target, outFile) {
	this->targetString = targetString;

	std::vector<std::string> header;
	header.push_back("Generation");
	for (unsigned int i = 0; i <= targetString.size(); i++)
		header.push_back(std::to_string(i));
	this->setHeader(header);
}

std::map<
	std::string,
	unsigned int
> GenerationHammingDistanceCSV::buildEmptyMap() {
	std::map<std::string, unsigned int> counts;
	for (unsigned int i = 0; i <= this->targetString.size(); i++)
		counts.emplace(std::to_string(i), 0);
	return counts;
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

void GenerationHammingDistanceCSV::reportDistances() {
	std::map<std::string, unsigned int> output = this->buildEmptyMap();
	output.emplace("Generation", this->target->currentGeneration());
	for (unsigned int i = 0; i < this->target->populationSize(); i++)
		output[std::to_string(
			this->checkHammingDistance(this->target->getIndex(i))
		)]++;
	this->write(output, (unsigned int)0);
}

void GenerationHammingDistanceCSV::initialReport() {
	this->reportDistances();
}

void GenerationHammingDistanceCSV::runtimeReport() {
	this->reportDistances();
}

void GenerationHammingDistanceCSV::endReport() {}
