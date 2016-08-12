#include "core/instruments/InstrumentCollection.hpp"
#include "core/instruments/HierInstrument.hpp"

InstrumentCollection::~InstrumentCollection() {
	for (auto instr: this->instruments) delete(instr);
	this->instruments.clear();
}

void InstrumentCollection::add(HierInstrument* instrument) {
	this->instruments.push_back(instrument);
}

void InstrumentCollection::add(std::vector<HierInstrument*> instruments) {
	this->instruments.insert(
		this->instruments.end(),
		instruments.begin(),
		instruments.end()
	);
}

void InstrumentCollection::runInitial() {
	for (auto instr: this->instruments) instr->initialReport();
}

void InstrumentCollection::runRuntime() {
	for (auto instr: this->instruments) instr->runtimeReport();
}

void InstrumentCollection::runEnd() {
	for (auto instr: this->instruments) instr->endReport();
}
