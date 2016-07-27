#include "objectives/noisy/fitness-noise/GaussianFitnessNoiseSource.hpp"
#include "core/HierRNG.hpp"

GaussianFitnessNoiseSource::GaussianFitnessNoiseSource(
	double stdDev
) : FitnessNoiseSource() {
	this->init(0, stdDev);
}

GaussianFitnessNoiseSource::GaussianFitnessNoiseSource(
	double mean,
	double stdDev
) : FitnessNoiseSource() {
	this->init(mean, stdDev);
}

void GaussianFitnessNoiseSource::init(double mean, double stdDev) {
	this->mean = mean;
	this->stdDev = stdDev;
}

float GaussianFitnessNoiseSource::addNoise(float cleanFitness) {
	return cleanFitness + HierRNG::gaussianRandomNumber(
		this->mean,
		this->stdDev
	);
}
