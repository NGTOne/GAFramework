#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/EvolutionarySystem.hpp"

using namespace std;

EvolutionarySystem::EvolutionarySystem(
	SelectionStrategy * strategy,
	CrossoverOperation * cross,
	MutationOperation * mutation
) {
	this->init(
		strategy,
		cross,
		mutation
	);
}

EvolutionarySystem::~EvolutionarySystem() {}

void EvolutionarySystem::registerInternalObjects(
	NodeGarbageCollector & collector
) {
	collector.registerObject(this->strategy);
	collector.registerObject(this->cross);
	collector.registerObject(this->mutation);
}

void EvolutionarySystem::init(
	SelectionStrategy * strategy,
	CrossoverOperation * cross,
	MutationOperation * mutation
) {
	this->strategy = strategy;
	this->cross = cross;
	this->mutation = mutation;
}

void EvolutionarySystem::sortPopulation(
	std::vector<Genome*> & population,
	std::vector<float> & fitnesses
) {
	for (unsigned int i = 0; i < population.size(); i++) {
		for (unsigned int k = 0; k < population.size(); k++) {
			if (fitnesses[i] > fitnesses[k]) {
				float tempFitness = fitnesses[i];
				Genome * tempSolution = population[i];
				fitnesses[i] = fitnesses[k];
				population[i] = population[k];
				fitnesses[k] = tempFitness;
				population[k] = tempSolution;
			}
		}
	}
}

float EvolutionarySystem::evaluateFitness(
	Genome * target,
	vector<ObjectiveFunction*> objectives
) {
	float finalFitness = 0;
	for (unsigned int i = 0; i < objectives.size(); i++)
		finalFitness += objectives[i]->checkFitness(target);

	return finalFitness;
}

unsigned int EvolutionarySystem::getParent(
	vector<Genome*> population,
	vector<float> fitnesses
) {
	return this->strategy->getParent(population, fitnesses);
}

vector<Genome*> EvolutionarySystem::produceChildren(
	vector<Genome*> parents,
	std::string speciesNode
) {
	vector<Genome*> children = this->cross->crossOver(parents, speciesNode);
	for (unsigned int i = 0; i < children.size(); i++) {
		Genome * temp = children[i];
		children[i] = this->mutation->mutate(children[i]);
		delete(temp);
	}

	return children;
}

string EvolutionarySystem::toString() {
        stringstream ss;
	
	ss << "Selection Strategy Info:\n";

	if (this->strategy) {
		ss << this->strategy->toString();
	} else {
		ss << "Not using any selection strategy\n";
	}

	return ss.str();
}

SelectionStrategy * EvolutionarySystem::getSelectionStrategy() {
	return this->strategy;
}

CrossoverOperation * EvolutionarySystem::getCrossover() {
	return this->cross;
}

MutationOperation * EvolutionarySystem::getMutation() {
	return this->mutation;
}

bool EvolutionarySystem::hasNiching() {
	return false;
}
