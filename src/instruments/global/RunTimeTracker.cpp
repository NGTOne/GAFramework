#include "instruments/global/RunTimeTracker.hpp"
#include <sstream>
#include <chrono>

RunTimeTracker::RunTimeTracker(
	HierarchicalEA* target,
	std::string outFile
) : GlobalInstrument(target, outFile) {
	this->tracking = false;
}

void RunTimeTracker::initialReport() {
	if (!this->tracking)
		this->startTime = std::chrono::high_resolution_clock::now();
	this->tracking = true;	
}

void RunTimeTracker::runtimeReport() {}

void RunTimeTracker::endReport() {
	auto endTime = std::chrono::high_resolution_clock::now();

	std::stringstream ss;
	ss << "Run took " << std::chrono::duration_cast<
		std::chrono::milliseconds
	>(endTime - this->startTime).count() << " milliseconds\n";
	this->write(ss.str());
}
