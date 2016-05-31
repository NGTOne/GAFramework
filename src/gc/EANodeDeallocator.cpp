#include "gc/EANodeDeallocator.hpp"
#include "nodes/EANode/EANode.hpp"
#include "nodes/EANode/EvolutionarySystem.hpp"
#include "nodes/EANode/CrossoverOperation.hpp"
#include "nodes/EANode/MutationOperation.hpp"
#include "nodes/EANode/SelectionStrategy.hpp"
#include "systems/niching/NichingStrategy.hpp"
#include "systems/SSGA.hpp"
#include <set>

EANodeDeallocator::EANodeDeallocator() {}
EANodeDeallocator::~EANodeDeallocator() {}

bool EANodeDeallocator::canDeleteNode(PopulationNode * node) {
	return node->type() == EA_TYPE;
}

void EANodeDeallocator::deleteNodes() {
	set<EvolutionarySystem*> systems;
	set<CrossoverOperation*> crossovers;
	set<MutationOperation*> mutations;
	set<SelectionStrategy*> selections;
	set<NichingStrategy*> niching;

	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		EANode * temp = (EANode*)this->nodes[i];

		EvolutionarySystem * system = temp->getSystem();
		systems.insert(system);
		crossovers.insert(temp->getCrossover());
		mutations.insert(temp->getMutation());
		selections.insert(system->getSelectionStrategy());

		if (system->hasNiching())
			niching.insert(((SSGA*)system)->getNiching());

		delete(temp);
	}

	this->clearSet<EvolutionarySystem*>(systems);
	this->clearSet<CrossoverOperation*>(crossovers);
	this->clearSet<MutationOperation*>(mutations);
	this->clearSet<SelectionStrategy*>(selections);
	this->clearSet<NichingStrategy*>(niching);
}
