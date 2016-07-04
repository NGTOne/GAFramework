#include "objectives/noisy/NoisyObjective.hpp"
#include "objectives/noisy/scramblers/NonScrambler.hpp"
#include <chrono>

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective
) : NestedObjective(cleanObjective) {
	this->init(
		new NonScrambler(),
		std::chrono::system_clock::now().time_since_epoch().count()
	);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	GeneScrambler * scrambler
) : NestedObjective(cleanObjective) {
	this->init(
		scrambler,
		std::chrono::system_clock::now().time_since_epoch().count()
	);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	unsigned int seed
) : NestedObjective(cleanObjective) {
	this->init(new NonScrambler(), seed);
}

NoisyObjective::NoisyObjective(
	ObjectiveFunction * cleanObjective,
	GeneScrambler * scrambler,
	unsigned int seed
) : NestedObjective(cleanObjective) {
	this->init(scrambler, seed);
}

void NoisyObjective::init(GeneScrambler * scrambler, unsigned int seed) {
	this->scrambler = scrambler;
	this->generator = std::mt19937(seed);
}

Genome NoisyObjective::addNoise(Genome * target) {
	return this->scrambler->scramble(target);
}

float NoisyObjective::checkFitness(Genome * genome) {
	Genome noisy = this->addNoise(genome);
	return this->addNoise(this->checkInnerFitness(&noisy));
}
