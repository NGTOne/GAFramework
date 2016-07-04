#include "objectives/noisy/fitness-noise/GaussianFitnessNoiseSource.hpp"

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

GaussianFitnessNoiseSource::GaussianFitnessNoiseSource(
	double mean,
	double stdDev,
	unsigned int seed
) : FitnessNoiseSource(seed) {
	this->init(mean, stdDev);
}

void GaussianFitnessNoiseSource::init(double mean, double stdDev) {
	this->modifierDist = std::normal_distribution<double>(mean, stdDev);
}

float GaussianFitnessNoiseSource::addNoise(float cleanFitness) {
	return cleanFitness + this->modifierDist(this->generator);
}
