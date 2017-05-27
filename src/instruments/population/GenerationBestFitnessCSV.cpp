#include "instruments/population/GenerationBestFitnessCSV.hpp"
#include <limits>
#include <sstream>

GenerationBestFitnessCSV::GenerationBestFitnessCSV(
	PopulationNode* target,
	std::string outFile
) : GenerationalCSVInstrument(target, outFile) {}

void GenerationBestFitnessCSV::report() {
	std::vector<Fitness> fitnesses = this->target->getFitnesses();
	Fitness bestFitness = Fitness::lowestPossible();

	for (Fitness fitness: fitnesses)
		if (fitness > bestFitness) bestFitness = fitness;

	this->fitnesses.push_back(bestFitness.collapse());
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
	this->write(this->fitnesses, std::numeric_limits<double>::lowest());
}
