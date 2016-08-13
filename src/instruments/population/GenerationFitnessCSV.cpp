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
	std::vector<std::string> headerBuckets;
	for (float i = bottomFitness; i <= topFitness; i+= resolution) {
		buckets.push_back(i);
		headerBuckets.push_back(std::to_string(i));
	}
	this->buckets = buckets;
	this->resolution = resolution;
	this->addToHeader("Generation");
	this->addToHeader(headerBuckets);
}

float GenerationFitnessCSV::bucket(float actual) {
	float mod = fmod(actual, this->resolution);

	return (mod < this->resolution/2 ?
		actual - mod : actual - mod + resolution);
}

std::map<std::string, unsigned int> GenerationFitnessCSV::buildEmptyMap() {
	std::map<std::string, unsigned int> counts;
	for (float fitness: this->buckets)
		counts.emplace(std::to_string(fitness), 0);
	return counts;
}

void GenerationFitnessCSV::reportFitnesses() {
	std::map<std::string, unsigned int> output = this->buildEmptyMap();
	output.emplace("Generation", this->target->currentGeneration());
	std::vector<float> fitnesses = this->target->getFitnesses();
	for (float fitness: fitnesses) output[std::to_string(fitness)]++;
	this->write(output, (unsigned int)0);
}

void GenerationFitnessCSV::initialReport() {
	this->reportFitnesses();
}

void GenerationFitnessCSV::runtimeReport() {
	this->reportFitnesses();
}

void GenerationFitnessCSV::endReport() {
	this->reportFitnesses();
}
