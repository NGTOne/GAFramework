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
	void write(std::vector<T> values);

	template <typename Val>
	void write(std::map<std::string, Val> values);

	template <typename T>
	void setHeader(std::vector<T> values);

	public:
};

template <typename T>
void CSVInstrument::write(std::vector<T> values) {
	if (!this->headerWritten) {
		this->write(this->header);
		this->headerWritten = true;
	}

	std::stringstream ss;

	for (unsigned int i = 0; i < values.size() - 1; i++)
		ss << values[i] << ",";
	ss << values[values.size() - 1];
	HierInstrument::write(ss.str());
}

template <typename Val>
void CSVInstrument::write(std::map<std::string, Val> values) {
	std::vector<Val> valuesToWrite;

	for (unsigned int i = 0; i < this->header.size(); i++)
		valuesToWrite.push_back(values.find(this->header[i])->second);

	this->write(valuesToWrite);
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
