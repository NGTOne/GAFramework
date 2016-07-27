#include "core/HierRNG.hpp"
#include <chrono>
#include <random>

unsigned int HierRNG::seed;
std::mt19937 HierRNG::generator;

void HierRNG::initialize() {
	HierRNG::seed = std::chrono::system_clock::now()
		.time_since_epoch().count();
	HierRNG::generator = std::mt19937(HierRNG::seed);
}

void HierRNG::initialize(unsigned int seed) {
	HierRNG::seed = seed;
	HierRNG::generator = std::mt19937(HierRNG::seed);
}

double HierRNG::gaussianRandomNumber(double mean, double stdDev) {
	std::normal_distribution<double> dist(mean, stdDev);
	return dist(HierRNG::generator);
}
