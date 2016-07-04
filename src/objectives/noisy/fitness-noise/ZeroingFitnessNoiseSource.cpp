#include "objectives/noisy/fitness-noise/ZeroingFitnessNoiseSource.hpp"

ZeroingFitnessNoiseSource::ZeroingFitnessNoiseSource(
	double zeroChance
) : FitnessNoiseSource() {
	this->init(zeroChance);
}

ZeroingFitnessNoiseSource::ZeroingFitnessNoiseSource(
	double zeroChance,
	unsigned int seed
) : FitnessNoiseSource(seed) {
	this->init(zeroChance);
}

void ZeroingFitnessNoiseSource::init(double zeroChance) {
	this->zeroChance = zeroChance;
	this->modifierDist = std::uniform_real_distribution<double>(0, 1);
}

float ZeroingFitnessNoiseSource::addNoise(float cleanFitness) {
	return ((this->modifierDist(this->generator) > this->zeroChance) ?
		cleanFitness : 0);
}
