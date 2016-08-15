#ifndef CORE_HIER_STRUCTURES_HierarchicalEA_instruments_t
#define CORE_HIER_STRUCTURES_HierarchicalEA_instruments_t

#include "../HierarchicalEA.hpp"
#include "../instruments/HierInstrument.hpp"
#include "../instruments/PopulationInstrument.hpp"
#include "../instruments/GlobalInstrument.hpp"
#include "../../exception/MismatchedCountsException.hpp"

template <typename InstrType, typename... params>
void HierarchicalEA::addGlobalInstrumentation(
	std::string outFile,
	params... as
) {
	static_assert(
		std::is_base_of<GlobalInstrument, InstrType>::value,
		"Type provided to addInstrumentation() does not operate globally!"
	);

	this->instruments.add(new InstrType(this, outFile, as...));
}

template <typename InstrType, typename... params>
void HierarchicalEA::addPopulationInstrumentation(
	std::string node,
	std::string outFile,
	params... as
) {
	this->addPopulationInstrumentation<InstrType>(
		std::vector<std::string>({node}),
		std::vector<std::string>({outFile}),
		as...
	);
}

template<typename InstrType, typename... params>
void HierarchicalEA::addPopulationInstrumentation(
	std::vector<std::string> nodes,
	std::string outFile,
	params... as
) {
	this->addPopulationInstrumentation<InstrType>(
		nodes,
		std::vector<std::string>(nodes.size(), outFile),
		as...
	);
}

template <typename InstrType, typename... params>
void HierarchicalEA::addPopulationInstrumentation(
	std::vector<std::string> nodes,
	std::vector<std::string> outFiles,
	params... as
) {
	static_assert(
		std::is_base_of<PopulationInstrument, InstrType>::value,
		"Type provided to addInstrumentation() does not operate on population nodes!"
	);

	if (!this->compareVectorLengths(nodes, outFiles))
		throw MismatchedCountsException("Number of nodes specified does not match number of output files for instrumentation.");

	for (unsigned int i = 0; i < nodes.size(); i++)
		this->instruments.add(new InstrType(
			this->getNodeByName(nodes[i]),
			outFiles[i],
			as...
		));
}

#endif
