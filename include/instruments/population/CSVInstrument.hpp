#ifndef INSTRUMENTS_POPULATION_CSVInstrument
#define INSTRUMENTS_POPULATION_CSVInstrument

#include "../../core/instruments/PopulationInstrument.hpp"
#include <vector>
#include <map>
#include <sstream>

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

	template <typename T>
	void setHeader(std::vector<T> values);

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

template <typename T>
void CSVInstrument::setHeader(std::vector<T> values) {
	std::stringstream ss;
	std::vector<std::string> header;
	for (auto it = values.begin(); it != values.end(); it++) {
		ss.str("");
		ss << it;
		header.push_back(ss.str());
	}

	this->header = header;	
}

#endif
