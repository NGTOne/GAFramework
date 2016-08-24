#include "instruments/population/CSVInstrument.hpp"

CSVInstrument::CSVInstrument(
	PopulationNode* target,
	std::string outFile
) : PopulationInstrument(target, outFile) {
	this->headerWritten = false;
}

template <>
std::string CSVInstrument::stringify<bool>(bool value) {
	return value ? "true" : "false";
}
