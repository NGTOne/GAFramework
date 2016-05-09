#include "core/PopulationNode.hpp"
#include <sstream>
#include <iostream>

using namespace std;

PopulationNode::PopulationNode(
	int populationSize,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string nodeName
) {
	init(
		populationSize,
		objectives,
		populationToString,
		conditions,
		nodeName,
		1
	);
}

PopulationNode::PopulationNode(
	int populationSize,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string nodeName,
	int accelerationFactor
) {
	init(
		populationSize,
		objectives,
		populationToString,
		conditions,
		nodeName,
		accelerationFactor
	);
}

PopulationNode::~PopulationNode() {
	for (int i = 0; i < population.size(); i++) {
		delete(population[i]);
	}
}

void PopulationNode::init(
	int populationSize,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string nodeName,
	int accelerationFactor
) {
	this->populationSize = populationSize;
	this->objectives = objectives;
	this->populationToString = populationToString;
	this->conditions = conditions;
	this->nodeName = nodeName;
	this->accelerationFactor = accelerationFactor;
}

void PopulationNode::addEndCondition(EndCondition * condition) {
	this->conditions.push_back(condition);
}

void PopulationNode::addEndConditions(vector<EndCondition*> conditions) {
	for (int i = 0; i < conditions.size(); i++) {
		this->conditions.push_back(conditions[i]);
	}
}

void PopulationNode::setEndCondition(EndCondition * condition) {
	this->conditions.clear();
	this->addEndCondition(condition);
}

void PopulationNode::setEndConditions(vector<EndCondition*> conditions) {
	this->conditions.clear();
	this->addEndConditions(conditions);
}

void PopulationNode::addLoci(string format, ...) {
	// TODO
}

void PopulationNode::nextIteration() {
	int i = 0;
	while (!done() && i++ < accelerationFactor) {
		evaluateFitnesses();
		population = getNextPopulation();
		evaluateFitnesses();
		// TODO: Work in apportionment
	}
}

Genome * PopulationNode::getIndex(int index) {
	return population[index];
}

bool PopulationNode::done() {
	// TODO: Allow logical operations (AND/OR) of end conditions
	for (int i = 0; i < conditions.size(); i++) {
		if (conditions[i]->checkCondition(
			population,
			fitnesses,
			currentIteration
		) == false) {
			return false;
		}
	}

	return true;
}

// Since our n is reasonably small, the O(n^2) bubblesort will suffice
void PopulationNode::sortPopulation() {
	for (int i = 0; i < population.size(); i++) {
		for (int k = 0; k < population.size(); k++) {
			if (fitnesses[i] > fitnesses[k]) {
				int tempFitness = fitnesses[i];
				vector<vector<int>> tempAssigned =
					assignedFitnesses[i];
				Genome * tempSolution = population[i];

				fitnesses[i] = fitnesses[k];
				assignedFitnesses[i] = assignedFitnesses[k];
				population[i] = population[k];

				fitnesses[k] = tempFitness;
				assignedFitnesses[k] = tempAssigned;
				population[k] = tempSolution;
			}
		}
	}
}

void PopulationNode::evaluateFitnesses() {
	for (int i = 0; i < population.size(); i++) {
		fitnesses[i] = this->evaluateFitness(i);
	}
}

void PopulationNode::insert(int index, Genome * target) {
	delete(population[index]);
	for (int i = 0; i < assignedFitnesses[index].size(); i++) {
		assignedFitnesses[index][i].clear();
	}
	this->evaluateFitness(index);
}

string PopulationNode::name() {
	return this->nodeName;
}

string PopulationNode::populationStrings() {
	stringstream ss;
	string populationString;
	
	for (int i = 0; i < population.size(); i++) {
		populationString = populationToString->toString(population[i]);

		ss << "Member " << i << ": " << populationString
			<< " Fitness: " << fitnesses[i] << "\n";
	}

	return ss.str();
}

string PopulationNode::toString() {
	stringstream ss;
	string populationString;

	ss << "Population size: " << population.size() << "\n";
	ss << populationStrings();

	readOnce = true;
	return ss.str();
}
