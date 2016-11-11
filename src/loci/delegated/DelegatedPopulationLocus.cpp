#include "loci/delegated/DelegatedPopulationLocus.hpp"

DelegatedPopulationLocus::DelegatedPopulationLocus(
	PopulationNode* target,
	DelegationStrategy* strategy
) : PopulationLocus(target) {
	this->strategy = strategy;
}

void DelegatedPopulationLocus::registerInternalObjects() {
	PopulationLocus::registerInternalObjects();
	HierGC::registerObject(this->strategy);
}

boost::any DelegatedPopulationLocus::getIndex(Gene* index) {
	return this->node->getIndex(this->strategy->getBestIndex(this->node));
}
