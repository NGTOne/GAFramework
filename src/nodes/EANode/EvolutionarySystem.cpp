#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/EvolutionarySystem.hpp"

using namespace std;

EvolutionarySystem::EvolutionarySystem(SelectionStrategy * strategy) {
	init(strategy, chrono::system_clock::now().time_since_epoch().count());
}

EvolutionarySystem::EvolutionarySystem(
	SelectionStrategy * strategy,
	unsigned seed
) {
	init(strategy, seed);
}

EvolutionarySystem::~EvolutionarySystem() {}

void EvolutionarySystem::init(SelectionStrategy * strategy, unsigned seed) {
	this->seed = seed;
	this->generator = mt19937(seed);
	this->strategy = strategy;
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
	CrossoverOperation * cross,
	MutationOperation * mutation,
	std::string speciesNode
) {
	vector<Genome*> children = cross->crossOver(parents, speciesNode);
	for (unsigned int i = 0; i < children.size(); i++) {
		Genome * temp = children[i];
		children[i] = mutation->mutate(children[i]);
		delete(temp);
	}

	return children;
}

string EvolutionarySystem::toString() {
        stringstream ss;
	
	ss << "Random seed: " << seed << "\nSelection Strategy Info:\n";

	if (strategy) {
		ss << this->strategy->toString();
	} else {
		ss << "Not using any selection strategy\n";
	}

	return ss.str();
}

SelectionStrategy * EvolutionarySystem::getSelectionStrategy() {
	return this->strategy;
}

bool EvolutionarySystem::hasNiching() {
	return false;
}
