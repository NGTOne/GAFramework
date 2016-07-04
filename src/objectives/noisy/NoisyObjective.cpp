#include "objectives/noisy/NoisyObjective.hpp"
#include "objectives/noisy/genetic-noise/NonNoisyGeneticSource.hpp"
#include <chrono>

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective
) : NestedObjective(cleanObjective) {
	this->init(
		new NonNoisyGeneticSource(),
		std::chrono::system_clock::now().time_since_epoch().count()
	);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	GeneticNoiseSource * geneticSource
) : NestedObjective(cleanObjective) {
	this->init(
		geneticSource,
		std::chrono::system_clock::now().time_since_epoch().count()
	);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	unsigned int seed
) : NestedObjective(cleanObjective) {
	this->init(new NonNoisyGeneticSource(), seed);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	GeneticNoiseSource * geneticSource,
	unsigned int seed
) : NestedObjective(cleanObjective) {
	this->init(geneticSource, seed);
}

void NoisyObjective::init(
	GeneticNoiseSource * geneticSource,
	unsigned int seed
) {
	this->geneticSource = geneticSource;
	this->generator = std::mt19937(seed);
}

Genome NoisyObjective::addNoise(Genome * target) {
	return this->geneticSource->addNoise(target);
}

float NoisyObjective::checkFitness(Genome * genome) {
	Genome noisy = this->addNoise(genome);
	return this->addNoise(this->checkInnerFitness(&noisy));
}
