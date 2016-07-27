#include "core/HierRNG.hpp"
#include <chrono>
#include <random>

void HierRNG::initialize() {
	HierRNG::seed = std::chrono::system_clock::now()
		.time_since_epoch().count();
	HierRNG::generator = std::mt19937(HierRNG::seed);
}

void HierRNG::initialize(unsigned int seed) {
	HierRNG::seed = seed;
	HierRNG::generator = std::mt19937(HierRNG::seed);
}
