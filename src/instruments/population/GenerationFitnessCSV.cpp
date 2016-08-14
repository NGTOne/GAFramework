#include "instruments/population/GenerationFitnessCSV.hpp"
#include <cmath>
#include <string>

GenerationFitnessCSV::GenerationFitnessCSV(
	PopulationNode* target,
	std::string outFile,
	float bottomFitness,
	float topFitness,
	float resolution
) : CSVInstrument(target, outFile) {
	std::vector<float> buckets;
	for (float i = bottomFitness; i <= topFitness; i+= resolution)
		buckets.push_back(i);

	this->buckets = buckets;
	this->resolution = resolution;
	this->addToHeader("Generation");
	this->addToHeader(buckets);
}

float GenerationFitnessCSV::bucket(float actual) {
	float mod = fmod(actual, this->resolution);

	return (mod < this->resolution/2 ?
		actual - mod : actual - mod + resolution);
}

void GenerationFitnessCSV::reportFitnesses() {
	auto output = this->buildEmptyMap(this->buckets, (unsigned int)0);
	output.emplace("Generation", this->target->currentGeneration());
	for (auto fitness: this->stringifyVector(this->target->getFitnesses()))
		output[fitness]++;
	this->write(output, (unsigned int)0);
}

void GenerationFitnessCSV::initialReport() {
	this->reportFitnesses();
}

void GenerationFitnessCSV::runtimeReport() {
	this->reportFitnesses();
}

// The same as the runtime report after the last generation
void GenerationFitnessCSV::endReport() {}
