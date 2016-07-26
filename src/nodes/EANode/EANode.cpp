#include "nodes/EANode/EANode.hpp"
#include <sstream>

using namespace std;

EANode::EANode(
	unsigned int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	EvolutionarySystem * system
) : PopulationNode(
	populationSize,
	loci,
	objectives,
	populationToString,
	conditions,
	name
) {
	this->init(system);
}

EANode::EANode(
	unsigned int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	unsigned int accelerationFactor,
	EvolutionarySystem * system
) : PopulationNode(
	populationSize,
	loci,
	objectives,
	populationToString,
	conditions,
	name,
	accelerationFactor
) {
	init(system);
}

void EANode::init(EvolutionarySystem * system) {
	this->system = system;
}

vector<Genome*> EANode::getNextPopulation() {
	return this->system->breedMutateSelect(
		this->population,
		this->fitnesses,
		this->objectives,
		this->nodeName
	);
}

string EANode::toString() {
	stringstream ss;

	ss << "Population size: " << this->population.size() << "\n";
	ss << populationStrings();

	if (this->readOnce == false) {
	        ss << "System Info:\n" << this->system->toString();
	}

	this->readOnce = true;
	return ss.str();
}

node_type_t EANode::type() {
	return EA_TYPE;
}

EvolutionarySystem * EANode::getSystem() {
	return this->system;
}

PopulationNode * EANode::duplicate(std::string newNodeName) {
	return new EANode(
		this->populationSize(),
		this->getCanonicalLoci(),
		this->getObjectives(),
		this->getToString(),
		this->getConditions(),
		newNodeName,
		this->accelerationFactor,
		this->getSystem()
	);
}
