#include "instruments/population/GenerationFitnessCSV.hpp"
#include <cmath>
#include <string>

GenerationFitnessCSV::GenerationFitnessCSV(
	PopulationNode* target,
	std::string outFile,
	float bottomFitness,
	float topFitness,
	float resolution
) : GenerationalCSVInstrument(target, outFile) {
	std::vector<float> buckets;
	for (float i = bottomFitness; i <= topFitness; i+= resolution)
		buckets.push_back(i);

	this->buckets = buckets;
	this->resolution = resolution;
	this->addToHeader("Generation");
	this->addToHeader(buckets);
}

float GenerationFitnessCSV::bucket(float actual) {
	if (actual < this->buckets[0]) return this->buckets[0];
	if (actual > this->buckets[this->buckets.size() - 1])
		return this->buckets[this->buckets.size() - 1];

	float mod = fmod(actual, this->resolution);

	return (mod < this->resolution/2 ?
		actual - mod : actual - mod + resolution);
}

void GenerationFitnessCSV::report() {
	auto output = this->buildEmptyMap(this->buckets, (unsigned int)0);
	output.emplace("Generation", this->target->currentGeneration());
	for (auto fitness: this->target->getFitnesses())
		output[this->stringify(this->bucket(fitness))]++;
	this->write(output, (unsigned int)0);
}
