#include "core/instruments/PopulationInstrument.hpp"
#include "core/PopulationNode.hpp"

PopulationInstrument::PopulationInstrument(
	PopulationNode* target,
	std::string outFile
) : HierInstrument(outFile) {
	this->target = target;
}
