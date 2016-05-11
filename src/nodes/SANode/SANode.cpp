#include "nodes/SANode/SANode.hpp"
#include "core/Locus.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

SANode::SANode(
	int populationSize,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	populationSize,
	objectives,
	populationToString,
	conditions,
	name
) {
	init(schedule, maximize);
}

SANode::SANode(
	int populationSize,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	populationSize,
	objectives,
	populationToString,
	conditions,
	name,
	accelerationFactor
) {
	init(schedule, maximize);
}

SANode::SANode(
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	1,
	objectives,
	populationToString,
	conditions,
	name
) {
	init(schedule, maximize);
}

SANode::SANode(
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	1,
	objectives,
	populationToString,
	conditions,
	name,
	accelerationFactor
) {
	init(schedule, maximize);
}

void SANode::init(bool maximize, TemperatureSchedule * schedule) {
	this->maximize = maximize;
	this->schedule = schedule;
}

vector<Genome*> SANode::getNextPopulation() {
	vector<Genome*> newPopulation;

	for (int i = 0; i < this->populationSize(); i++) {
		newPopulation.push_back(getNeighbour(this->population[i]));
	}

	return newPopulation;
}

int SANode::compareNeighbourliness(Genome * base, Genome * target) {
	return base->difference(target);
}

vector<Genome*> SANode::getAllNeighbours(Genome * target) {
	vector<Genome*> neighbours;
	vector<Locus*> loci = target->getLoci();

	for (int i = 0; i < target->genomeLength(); i++) {
		if (loci[i]->isConstructive()) {
			Genome * nearestKnownNeighbour;
			int top = loci[i]->topIndex();
			int lowestDiff = 0;

			for (int k = 0; k <= top; k++) {
				
			}
		} else {
			// For simple locus types, just increment/decrement
			// and be done with it
			vector<int> rawGenes = target->getGenome();
			if (!loci[i]->outOfRange(rawGenes[i]+1)) {
				rawGenes[i]++;
				neighbours.push_back(
					new Genome(rawGenes, loci)
				);
				rawGenes[i]--;
			}

			if (!loci[i]->outOfRange(rawGenes[i]-1)) {
				rawGenes[i]--;
				neighbours.push_back(
					new Genome(rawGenes, loci)
				);
			}
		}
	}

	return neighbours;
}

Genome * SANode::getNeighbour(Genome * target) {
	
}

// Oh God, why did I write it like this?
Individual * SimulatedAnnealer::getNeighbour(Individual * target) {
	int genomeLength = target->getGenomeLength();
	Individual ** neighbours = (Individual**)malloc(
		sizeof(Individual*)*genomeLength
	);
	Individual * temp;
	Genome * tempGenome;

	Genome * baseGenome = target->getGenome();
	GeneNode ** nodes = baseGenome->getGeneNodes();
	int * genes = baseGenome->getGenome();
	int diff;

	for (int i = 0; i < genomeLength; i++) {
		int lowestDiff = 0;
		Individual * nearestKnownNeighbour = NULL;

		// Since we don't know where our nearest neighbour is in a
		// population of components, we have to cycle through them all
		int numAlleles = nodes[i]->getPopulationSize();
		for (int k = 0; k < numAlleles; k++) {
			if (genes[i] == k) {
				if (k < numAlleles - 1) {
					k++;
				} else {
					break;
				}
			}

			int * tempGenes = (int*)malloc(
				sizeof(int)*genomeLength
			);

			for (int c = 0; c < genomeLength; c++) {
				tempGenes[c] = genes[c]; // Reset
			}

			tempGenes[i] = k;

			tempGenome = new Genome(
				tempGenes,
				genomeLength,
				nodes
			);

			temp = target->copyWithNewGenome(tempGenome);
			delete(tempGenome);
			free(tempGenes);
			diff = compareNeighbourliness(target, temp);

			if ((diff < lowestDiff && diff > 0) || lowestDiff == 0) {
				delete(nearestKnownNeighbour);
				nearestKnownNeighbour = temp;
				lowestDiff = diff;
			} else {
				delete(temp);
			}
		}

		if (lowestDiff == 0) {
			// The lowest diff being zero means that we have no
			// neighbours (i.e. all the available choices result
			// in no change)
			neighbours[i] = NULL;
		} else {
			neighbours[i] = nearestKnownNeighbour;
		}
	}

	uniform_int_distribution<int> neighbourDistribution(0, genomeLength-1);
	int choice = neighbourDistribution(generator);

	// Make sure we're not picking identical values over and over again
	for (int i = 0; i < genomeLength && neighbours[choice] == NULL; i++) {
		choice = neighbourDistribution(generator);
	}

	if (neighbours[choice] == NULL) return target->deepCopy();

	int targetFitness = target->checkFitness();
	int neighbourFitness = neighbours[choice]->checkFitness();

	Individual * neighbour = neighbours[choice]->deepCopy();
	for (int i = 0; i < genomeLength; i++) {
		delete(neighbours[i]);
	}

	free(neighbours);

	if (
		(maximize && targetFitness < neighbourFitness) ||
		(!maximize && targetFitness > neighbourFitness)
	) {
		return neighbour;
	} else {
		float temp = schedule->currentTemp(currentGeneration);
		if (temp == 0) {
			delete(neighbour);
			return target->deepCopy();
		}

		int delta = maximize ? neighbourFitness - targetFitness :
			targetFitness - neighbourFitness;

		float probability = exp(((float)delta)/temp);

		uniform_real_distribution<float>
			goingWrongWayDistribution(0, 1);

		if (goingWrongWayDistribution(generator) < probability) {
			return neighbour;
		} else {
			return target->deepCopy();
		}
	}
}

string SimulatedAnnealer::toString() {
	stringstream ss;

	ss << "Population size: " << populationSize << "\n";
	ss << populationStrings();

	if (!readOnce) ss << "Seed: " << seed << "\n";
	readOnce = true;

	return ss.str();
}
