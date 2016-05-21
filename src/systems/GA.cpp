#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "systems/GA.hpp"

using namespace std;

GA::GA(
	int numElites,
	bool randomElitePlacement,
	SelectionStrategy * strategy
) : EvolutionarySystem(strategy) {
	init(numElites, randomElitePlacement);
}

GA::GA(
	int numElites,
	SelectionStrategy * strategy
) : EvolutionarySystem(strategy) {
	init(numElites, false);
}

GA::GA(
	int numElites,
	bool randomElitePlacement,
	SelectionStrategy * strategy,
	unsigned seed
) : EvolutionarySystem(strategy, seed) {
	init(numElites, randomElitePlacement);
}

void GA::init(int numElites, bool randomElitePlacement) {
	this->numElites = numElites;
	this->randomElitePlacement = randomElitePlacement;
}

void GA::placeElites(
	vector<Genome*> initialPopulation,
	vector<int> initialPopulationFitnesses,
	vector<Genome*> & newPopulation,
	vector<int> & newPopulationFitnesses
) {
	vector<int> eliteLocations = this->findElites(
		initialPopulationFitnesses
	);

	for (int i = 0; i < eliteLocations.size(); i++) {
		if (!randomElitePlacement) {
			newPopulation[i] =
				initialPopulation[eliteLocations[i]];
			newPopulationFitnesses[i] =
				initialPopulationFitnesses[eliteLocations[i]];
		} else {
			uniform_int_distribution<int> dist(
				0,
				initialPopulation.size()-1
			);
			int index;

			do {
				index = dist(generator);
			} while (newPopulation[index] != NULL);
			newPopulation[index] =
				initialPopulation[eliteLocations[i]];
			newPopulationFitnesses[index] =
				initialPopulationFitnesses[eliteLocations[i]];
		}
	}
}

vector<int> GA::findElites(vector<int> fitnesses) {
	int populationSize = fitnesses.size(), bestFitness, bestFitnessIndex;
	bool eliteLocations[populationSize];
	vector<int> eliteIndexes;
	for (int i = 0; i < populationSize; i++) eliteLocations[i] = false;
	int numElites = this->numElites >= fitnesses.size() ?
		this->numElites/2 : this->numElites;

	for (int i = 0; i < numElites; i++) {
		bestFitness = 0;
		for (int k = 0; k < populationSize; i++) {
			if (
				fitnesses[k] > bestFitness
				&& eliteLocations[k] == false
			) {
				bestFitnessIndex = k;
				bestFitness  = fitnesses[k];
			}
		}

		eliteLocations[bestFitnessIndex] = true;
	}

	for (int i = 0; i < populationSize; i++) {
		if (eliteLocations[i]) eliteIndexes.push_back(i);
	}

	return eliteIndexes;
}

vector<Genome*> GA::breedMutateSelect(
	vector<Genome*> initialPopulation,
	vector<int> & populationFitnesses,
	CrossoverOperation * cross,
	MutationOperation * mutation,
	vector<ObjectiveFunction*> objectives
) {
	vector<Genome*> newPopulation(initialPopulation.size(), NULL);
	vector<int> newFitnesses(initialPopulation.size(), 0);

	this->placeElites(
		initialPopulation,
		populationFitnesses,
		newPopulation,
		newFitnesses
	);

	int numOffspring = this->numElites;
	while(numOffspring < initialPopulation.size()) {
		vector<Genome*> parents;
		vector<Genome*> children;
		for (int i = 0; i < 2; i++) parents.push_back(
			initialPopulation[this->getParent(
				initialPopulation,
				populationFitnesses
			)]
		);

		children = this->produceChildren(parents, cross, mutation);

		for (
			int i = 0;
			numOffspring < initialPopulation.size(); 
			i++
		) {
			newPopulation[numOffspring++] = children[i];
		}
	}

	for (int i = 0; i < newPopulation.size(); i++) {
		populationFitnesses[i] = this->evaluateFitness(
			newPopulation[i],
			objectives
		);
	}

	return newPopulation;
}
