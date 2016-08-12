#ifndef CORE_HIER_STRUCTURES_HierarchicalEA_Instruments_t
#define CORE_HIER_STRUCTURES_HierarchicalEA_Instruments_t

#include "../HierarchicalEA.hpp"
#include "../instruments/HierInstrument.hpp"
#include "../instruments/PopulationInstrument.hpp"
#include "../instruments/GlobalInstrument.hpp"
#include "../../exception/MismatchedCountsException.hpp"

template <typename InstrType>
void HierarchicalEA::addInstrumentation(
	std::string outFile,
	bool runImmediately
) {
	static_assert(
		std::is_base_of<GlobalInstrument, InstrType>::value,
		"Type provided to addInstrumentation() does not operate globally!"
	);

	HierInstrument* instrument = new InstrType(this, outFile);
	this->instruments.add(instrument);
	if (runImmediately) instrument->initialReport();
}

template <typename InstrType>
void HierarchicalEA::addInstrumentation(
	std::string node,
	std::string outFile,
	bool runImmediately
) {
	this->addInstrumentation<InstrType>({node}, {outFile}, runImmediately);
}

template<typename InstrType>
void HierarchicalEA::addInstrumentation(
	std::vector<std::string> nodes,
	std::string outFile,
	bool runImmediately
) {
	this->addInstrumentation<InstrType>(
		nodes,
		std::vector<std::string>(nodes.size(), outFile),
		runImmediately
	);
}

template <typename InstrType>
void HierarchicalEA::addInstrumentation(
	std::vector<std::string> nodes,
	std::vector<std::string> outFiles,
	bool runImmediately
) {
	static_assert(
		std::is_base_of<PopulationInstrument, InstrType>::value,
		"Type provided to addInstrumentation() does not operate on population nodes!"
	);

	if (!this->compareVectorLengths(nodes, outFiles))
		throw MismatchedCountsException("Number of nodes specified does not match number of output files for instrumentation.");

	std::vector<HierInstrument*> newInstruments;
	for (unsigned int i = 0; i < nodes.size(); i++)
		newInstruments.push_back(new InstrType(
			this->getNodeByName(nodes[i]),
			outFiles[i]
		));

	this->instruments.add(newInstruments);

	if (runImmediately)
		for (auto instr: newInstruments) instr->initialReport();
}

#endif
