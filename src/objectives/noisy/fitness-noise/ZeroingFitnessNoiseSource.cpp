#include "objectives/noisy/fitness-noise/ZeroingFitnessNoiseSource.hpp"
#include "core/utils/HierRNG.hpp"

ZeroingFitnessNoiseSource::ZeroingFitnessNoiseSource(
	double zeroChance
) : FitnessNoiseSource() {
	this->init(zeroChance);
}

void ZeroingFitnessNoiseSource::init(double zeroChance) {
	this->zeroChance = zeroChance;
}

float ZeroingFitnessNoiseSource::addNoise(float cleanFitness) {
	return HierRNG::chooseWithProb<float>(this->zeroChance, 0, cleanFitness);
}
