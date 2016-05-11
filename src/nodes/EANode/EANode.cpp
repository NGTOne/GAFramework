#include "nodes/EANode/EANode.hpp"
#include <sstream>

using namespace std;

EANode::EANode(
	int populationSize,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	EvolutionarySystem * system,
	CrossoverOperation * cross,
	MutationOperation * mutation
) : PopulationNode(
	populationSize,
	objectives,
	populationToString,
	conditions,
	name
) {
	init(system, cross, mutation);
}

EANode::EANode(
	int populationSize,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	int accelerationFactor,
	EvolutionarySystem * system,
	CrossoverOperation * cross,
	MutationOperation * mutation
) : PopulationNode(
	populationSize,
	objectives,
	populationToString,
	conditions,
	name,
	accelerationFactor
) {
	init(system, cross, mutation);
}

void EANode::init(
	EvolutionarySystem * system,
	CrossoverOperation * cross,
	MutationOperation * mutation
) {
	this->system = system;
	this->cross = cross;
	this->mutation = mutation;
}

vector<Genome*> EANode::getNextPopulation() {
	return this->system->breedMutateSelect(
		this->population,
		this->fitnesses
	);
}

string EANode::toString() {
	stringstream ss;

	ss << "Population size: " << this->population.size() << "\n";
	ss << populationStrings();

	if (readOnce == false) {
	        ss << "Selection Info:\n" << this->system->toString();
	        ss << "Crossover Info:\n" << this->cross->toString();
	        ss << "Mutation Info:\n" << this->mutation->toString();
	}

	readOnce = true;
	return ss.str();
}
