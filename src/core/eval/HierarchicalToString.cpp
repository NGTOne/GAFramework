#include "core/eval/HierarchicalToString.hpp"
#include "loci/PopulationLocus.hpp"
#include <sstream>

HierarchicalToString::HierarchicalToString(
	HierarchicalToString::mode printMode
) {
	this->printMode = printMode;
}

HierarchicalToString::~HierarchicalToString() {}

std::string HierarchicalToString::toString(Genome* genome) {
	if (this->printMode == HierarchicalToString::flatten)
		return this->stringifySegment(
			genome->flattenGenome().getGenome()
		);

	std::vector<Gene*> genes = genome->getGenome();
	std::stringstream ss;

	std::vector<Gene*> segment;
	for (unsigned int i = 0; i < genes.size(); i++) {
		if (!genes[i]->isConstructive()) {
			segment.push_back(genes[i]);
		} else {
			ss << this->stringifySegment(segment);
			segment.clear();
			if (
				this->printMode ==
					HierarchicalToString::printPlaceholders
			) {
				ss << " ["
					<< ((PopulationLocus*)genes[i]
						->getLocus()
					)->nodeName()
					<< ":"
					<< genes[i]->getIndex()
					<< "] ";
			}
		}
	}

	ss << this->stringifySegment(segment);

	return ss.str();
}

HierarchicalToString::mode HierarchicalToString::getPrintMode() {
	return this->printMode;
}

bool HierarchicalToString::isHierarchical() {
	return true;
}
