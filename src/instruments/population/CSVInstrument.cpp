#include "instruments/population/CSVInstrument.hpp"

CSVInstrument::CSVInstrument(
	PopulationNode* target,
	std::string outFile
) : PopulationInstrument(target, outFile) {
	this->headerWritten = false;
}

void CSVInstrument::setHeader(std::vector<std::string> values) {
	this->header = values;
}

void CSVInstrument::addToHeader(std::string value) {
	this->addToHeader(std::vector<std::string>({value}));
}

void CSVInstrument::addToHeader(std::vector<std::string> values) {
	this->header.insert(
		this->header.end(),
		values.begin(),
		values.end()
	);
}

