#include "core/PopulationNode.hpp"
#include <sstream>
#include <iostream>

using namespace std;

PopulationNode::PopulationNode(
	int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string nodeName
) {
	init(
		populationSize,
		loci,
		objectives,
		populationToString,
		conditions,
		nodeName,
		1
	);
}

PopulationNode::PopulationNode(
	int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string nodeName,
	int accelerationFactor
) {
	init(
		populationSize,
		loci,
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
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string nodeName,
	int accelerationFactor
) {
	this->initialPopulationSize = populationSize;
	this->objectives = objectives;
	this->populationToString = populationToString;
	this->conditions = conditions;
	this->nodeName = nodeName;
	this->accelerationFactor = accelerationFactor;

	this->createLoci(loci);
}

int PopulationNode::evaluateFitness(Genome * target) {
	int total = 0;
	for (int i = 0; i < this->objectives.size(); i++)
		total += this->objectives[i]->checkFitness(target);

	return total;
}

int PopulationNode::evaluateFitness(int solutionIndex) {
	Genome * genome = this->getIndex(solutionIndex);
	return this->evaluateFitness(genome);
}

void PopulationNode::createLoci(vector<Locus*> loci) {
	for (int i = 0; i < this->population.size(); i++) 
		delete(this->population[i]);
	this->population.clear();

	for (int i = 0; i < this->initialPopulationSize; i++)
		this->population.push_back(new Genome(loci));
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

void PopulationNode::addLoci(vector<Locus*> loci) {
	vector<Locus*> templateLoci = this->population[0]->getLoci();
	for (int i = 0; i < loci.size(); i++) {
		templateLoci.push_back(loci[i]);
	}

	this->createLoci(templateLoci);
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
				Genome * tempSolution = population[i];

				fitnesses[i] = fitnesses[k];
				population[i] = population[k];

				fitnesses[k] = tempFitness;
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
	this->evaluateFitness(index);
}

string PopulationNode::name() {
	return this->nodeName;
}

int PopulationNode::populationSize() {
	return this->population.empty() ?
		initialPopulationSize : population.size();
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

	ss << "Population size: " << population.size() << "\n";
	ss << populationStrings();

	readOnce = true;
	return ss.str();
}
