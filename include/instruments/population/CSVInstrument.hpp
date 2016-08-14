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
	std::vector<std::string> stringifyVector(std::vector<T> values);

	template <typename Key, typename Val>
	std::map<std::string, Val> buildEmptyMap(
		std::vector<Key> keys,
		Val emptyValue
	);

	template <typename T>
	void write(std::vector<T> values, T defaultValue);

	template <typename Val>
	void write(std::map<std::string, Val> values, Val defaultValue);

	template <typename T>
	void setHeader(std::vector<T> values);

	template <typename T>
	void addToHeader(T value);

	template <typename T>
	void addToHeader(std::vector<T> values);

	public:
};

template <typename T>
std::vector<std::string> CSVInstrument::stringifyVector(
	std::vector<T> values
) {
	std::vector<std::string> output;
	std::stringstream ss;
	for (T value: values) {
		ss.str("");
		ss << value;
		output.push_back(ss.str());
	}

	return output;
}

template <typename Key, typename Val>
std::map<std::string, Val> CSVInstrument::buildEmptyMap(
	std::vector<Key> keys,
	Val emptyValue
) {
	std::vector<std::string> stringKeys = this->stringifyVector(keys);
	std::map<std::string, Val> emptyValues;
	for (std::string key: stringKeys) emptyValues.emplace(key, emptyValue);
	return emptyValues;
}

template <typename T>
void CSVInstrument::write(std::vector<T> values, T defaultValue) {
	if (!this->headerWritten) {
		this->headerWritten = true;
		this->write(this->header, std::string());
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
	ss << "\n";

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
	std::vector<std::string> stringValues = this->stringifyVector(values);
	this->header = stringValues;
}

template <typename T>
void CSVInstrument::addToHeader(T value) {
	std::vector<T> vecVal({value});
	std::vector<std::string> stringValues = this->stringifyVector(vecVal);
	this->addToHeader<std::string>(stringValues);
}

template <typename T>
void CSVInstrument::addToHeader(std::vector<T> values) {
	std::vector<std::string> stringValues = this->stringifyVector(values);
	this->header.insert(
		this->header.end(),
		stringValues.begin(),
		stringValues.end()
	);
}

#endif
