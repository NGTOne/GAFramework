#include "core/eval/HierarchicalToString.hpp"
#include "loci/PopulationLocus.hpp"
#include <sstream>

HierarchicalToString::HierarchicalToString(bool printPlaceholders) {
	this->printPlaceholders = printPlaceholders;
}

HierarchicalToString::~HierarchicalToString() {}

std::string HierarchicalToString::toString(Genome* genome) {
	std::vector<Gene*> genes = genome->getGenome();
	std::stringstream ss;

	std::vector<Gene*> segment;
	for (unsigned int i = 0; i < genes.size(); i++) {
		if (!genes[i]->isConstructive()) {
			segment.push_back(genes[i]);
		} else {
			ss << this->stringifySegment(segment);
			segment.clear();
			if (this->printPlaceholders) ss << " ["
				<< ((PopulationLocus*)genes[i]->getLocus())
					->nodeName()
				<< ":"
				<< genes[i]->getIndex()
				<< "] ";
		}
	}

	return ss.str();
}
