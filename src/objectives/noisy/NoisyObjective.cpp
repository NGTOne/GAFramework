#include "objectives/noisy/NoisyObjective.hpp"
#include <chrono>

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective
) : NestedObjective(cleanObjective) {
	this->generator = std::mt19937(
		chrono::system_clock::now().time_since_epoch().count()
	);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	unsigned int seed
) : NestedObjective(cleanObjective) {
	this->generator = std::mt19937(seed);
}

float NoisyObjective::checkFitness(Genome * genome) {
	return this->addNoise(this->checkInnerFitness(genome));
}
