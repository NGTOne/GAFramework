#include "core/instruments/GlobalInstrument.hpp"
#include "core/HierarchicalEA.hpp"

GlobalInstrument::GlobalInstrument(
	HierarchicalEA* target,
	std::string outFile
) : HierInstrument(outFile) {
	this->target = target;
}
