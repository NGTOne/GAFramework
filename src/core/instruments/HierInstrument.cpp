#include "core/instruments/HierInstrument.hpp"
#include "core/utils/HierLogger.hpp"

HierInstrument::HierInstrument(std::string outFile) {
	this->outFile = outFile;
}

void HierInstrument::write(std::string message) {
	HierLogger::log(message, this->outFile);
}
