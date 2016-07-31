#include "objectives/noisy/NoisyObjective.hpp"
#include "objectives/noisy/genetic-noise/NonNoisyGeneticSource.hpp"
#include "objectives/noisy/fitness-noise/NonNoisyFitnessSource.hpp"
#include "core/HierGC.hpp"
#include <chrono>

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	GeneticNoiseSource * geneticSource
) : NestedObjective(cleanObjective) {
	this->init(geneticSource, new NonNoisyFitnessSource());
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	FitnessNoiseSource * fitnessSource
) : NestedObjective(cleanObjective) {
	this->init(new NonNoisyGeneticSource(), fitnessSource);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	GeneticNoiseSource * geneticSource,
	FitnessNoiseSource * fitnessSource
) : NestedObjective(cleanObjective) {
	this->init(geneticSource, fitnessSource);
}

void NoisyObjective::registerInternalObjects() {
	NestedObjective::registerInternalObjects();
	HierGC::registerObject(this->geneticSource);
	HierGC::registerObject(this->fitnessSource);
}

void NoisyObjective::init(
	GeneticNoiseSource * geneticSource,
	FitnessNoiseSource * fitnessSource
) {
	this->geneticSource = geneticSource;
	this->fitnessSource = fitnessSource;
}

Genome NoisyObjective::addNoise(Genome * target) {
	return this->geneticSource->addNoise(target);
}

float NoisyObjective::checkFitness(Genome * genome) {
	Genome noisy = this->addNoise(genome);
	return this->fitnessSource->addNoise(this->checkInnerFitness(&noisy));
}
