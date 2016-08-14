#include "instruments/population/GenerationalCSVInstrument.hpp"

GenerationalCSVInstrument::GenerationalCSVInstrument(
	PopulationNode* target,
	std::string outFile
) : CSVInstrument(target, outFile) {}

void GenerationalCSVInstrument::initialReport() {
	this->report();
}

void GenerationalCSVInstrument::runtimeReport() {
	this->report();
}

// It'll just be the same as the last runtime report
void GenerationalCSVInstrument::endReport() {}
