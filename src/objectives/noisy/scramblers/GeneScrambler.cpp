#include "objectives/noisy/scramblers/GeneScrambler.hpp"
#include <chrono>

GeneScrambler::GeneScrambler() {
	this->generator = std::mt19937(
		std::chrono::system_clock::now().time_since_epoch().count()
	);
}

GeneScrambler::GeneScrambler(unsigned int seed) {
	this->generator = std::mt19937(seed);
}
