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
	return (HierRNG::zeroOne<double>() > this->zeroChance ?
		cleanFitness : 0);
}
