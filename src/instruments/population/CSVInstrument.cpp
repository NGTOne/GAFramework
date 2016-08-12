#include "instruments/population/CSVInstrument.hpp"

CSVInstrument::CSVInstrument(
	PopulationNode* target,
	std::string outFile
) : PopulationInstrument(target, outFile) {}
