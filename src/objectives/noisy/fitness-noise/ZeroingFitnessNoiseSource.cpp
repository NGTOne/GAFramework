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

Fitness ZeroingFitnessNoiseSource::addNoise(Fitness cleanFitness) {
	return this->noisify(cleanFitness, [this](double component) -> double {
		return HierRNG::chooseWithProb<double>(
			this->zeroChance,
			0,
			component
		);
	});
}
