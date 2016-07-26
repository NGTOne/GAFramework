#include "objectives/noisy/fitness-noise/FitnessNoiseSource.hpp"
#include <chrono>

FitnessNoiseSource::FitnessNoiseSource() {
	this->generator = std::mt19937(
		std::chrono::system_clock::now().time_since_epoch().count()
	);
}

FitnessNoiseSource::FitnessNoiseSource(unsigned int seed) {
	this->generator = std::mt19937(seed);
}

void FitnessNoiseSource::registerInternalObjects(
	NodeGarbageCollector & collector
) {}
