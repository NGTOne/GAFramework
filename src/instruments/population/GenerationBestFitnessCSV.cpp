#include "instruments/population/GenerationBestFitnessCSV.hpp"
#include <limits>
#include <sstream>

GenerationBestFitnessCSV::GenerationBestFitnessCSV(
	PopulationNode* target,
	std::string outFile
) : GenerationalCSVInstrument(target, outFile) {}

void GenerationBestFitnessCSV::report() {
	std::vector<float> fitnesses = this->target->getFitnesses();
	float bestFitness = std::numeric_limits<float>::lowest();

	for (float fitness: fitnesses)
		if (fitness > bestFitness) bestFitness = fitness;

	this->fitnesses.push_back(bestFitness);
}

void GenerationBestFitnessCSV::endReport() {
	std::vector<std::string> headers;
	std::stringstream ss;

	for (unsigned int i = 0; i < this->fitnesses.size(); i++) {
		ss.str("");
		ss << "Generation " << i;
		headers.push_back(ss.str());
	}

	this->setHeader(headers);
	this->write(this->fitnesses, std::numeric_limits<float>::lowest());
}
