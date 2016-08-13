#ifndef INSTRUMENTS_POPULATION_CSVInstrument
#define INSTRUMENTS_POPULATION_CSVInstrument

#include "../../core/instruments/PopulationInstrument.hpp"
#include <vector>
#include <map>
#include <sstream>
#include <string>

class CSVInstrument: public PopulationInstrument {
	private:

	protected:
	std::vector<std::string> header;
	bool headerWritten;

	CSVInstrument(PopulationNode* target, std::string outFile);

	template <typename T>
	void write(std::vector<T> values, T defaultValue);

	template <typename Val>
	void write(std::map<std::string, Val> values, Val defaultValue);

	void setHeader(std::vector<std::string> values);
	void addToHeader(std::string value);
	void addToHeader(std::vector<std::string> values);

	public:
};

template <typename T>
void CSVInstrument::write(std::vector<T> values, T defaultValue) {
	if (!this->headerWritten) {
		this->write(this->header, std::string());
		this->headerWritten = true;
	}

	std::stringstream ss;

	for (unsigned int i = 0; i < values.size() - 1; i++)
		ss << values[i] << ",";
	ss << values[values.size() - 1];

	if (values.size() < this->header.size()) {
		for (
			unsigned int i = values.size();
			i < this->header.size() - 1;
			i++
		) ss << defaultValue << ",";
		ss << defaultValue;
	}

	HierInstrument::write(ss.str());
}

template <typename Val>
void CSVInstrument::write(std::map<std::string, Val> values, Val defaultValue) {
	std::vector<Val> valuesToWrite;

	for (unsigned int i = 0; i < this->header.size(); i++) {
		auto it = values.find(this->header[i]);
		if (it != values.end()) {
			valuesToWrite.push_back(it->second);
		} else {
			valuesToWrite.push_back(defaultValue);
		}
	}

	this->write(valuesToWrite, defaultValue);
}

#endif
