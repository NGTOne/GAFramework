#include "instruments/population/GenerationFitnessCSV.hpp"
#include <cmath>
#include <string>

GenerationFitnessCSV::GenerationFitnessCSV(
	PopulationNode* target,
	std::string outFile,
	double bottomFitness,
	double topFitness,
	double resolution
) : GenerationalCSVInstrument(target, outFile) {
	std::vector<double> buckets;
	for (double i = bottomFitness; i <= topFitness; i+= resolution)
		buckets.push_back(i);

	this->buckets = buckets;
	this->resolution = resolution;
	this->addToHeader("Generation");
	this->addToHeader(buckets);
}

double GenerationFitnessCSV::bucket(Fitness actual) {
	double collapsed = actual.collapse();
	if (collapsed < this->buckets[0]) return this->buckets[0];
	if (collapsed > this->buckets[this->buckets.size() - 1])
		return this->buckets[this->buckets.size() - 1];

	double mod = fmod(collapsed, this->resolution);

	return (mod < this->resolution/2 ?
		collapsed - mod : collapsed - mod + resolution);
}

void GenerationFitnessCSV::report() {
	auto output = this->buildEmptyMap(this->buckets, (unsigned int)0);
	output.emplace("Generation", this->target->currentGeneration());
	for (auto fitness: this->target->getFitnesses())
		output[this->stringify(this->bucket(fitness))]++;
	this->write(output, (unsigned int)0);
}
