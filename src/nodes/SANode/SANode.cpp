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

// TODO: Break this down further at some point
vector<Genome*> SANode::getAllNeighbours(Genome * target) {
	vector<Genome*> neighbours;
	vector<Locus*> loci = target->getLoci();
	vector<int> rawGenes = target->getGenome();
	vector<int> tempGenes = rawGenes;

	for (int i = 0; i < target->genomeLength(); i++) {
		if (loci[i]->isConstructive()) {
			Genome * nearestKnownNeighbour, tempGenome;
			int top = loci[i]->topIndex();
			int lowestDiff = 0, diff = 0;

			for (int k = 0; k <= top; k++) {
				// So we're not checking against ourselves
				if (rawGenes[i] == k) (k < top) ? k++ : break;

				tempGenes = rawGenes;
				tempGenes[i] = k;
				tempGenome = new Genome(tempGenes, loci);

				diff = this->compareNeighbourliness(
					target,
					tempGenome
				);

				if ((diff < lowestDiff && diff > 0)
					|| lowestDiff == 0
				) {
					delete(nearestKnownNeighbour);
					nearestKnownNeighbour = tempGenome;
					lowestDiff = diff;
				} else {
					delete(tempGenome);
				}
			}

			if (lowestDiff > 0) {
				neighbours.push_back(nearestKnownNeighbour);
			}
		} else {
			// For simple locus types, just increment/decrement
			// and be done with it
			if (!loci[i]->outOfRange(rawGenes[i]+1)) {
				tempGenes[i]++;
				neighbours.push_back(
					new Genome(rawGenes, loci)
				);
			}

			tempGenes = rawGenes;
			if (!loci[i]->outOfRange(rawGenes[i]-1)) {
				tempGenes[i]--;
				neighbours.push_back(
					new Genome(rawGenes, loci)
				);
			}
		}
	}

	return neighbours;
}

Genome * SANode::getNeighbour(Genome * target) {
	vector<Genome*> neighbours = this->getAllNeighbours(target);
	uniform_int_distribution<int> neighbourDist(0, neighbours.size() - 1);
	int neighbour = neighbourDistribution(generator);
}

// Oh God, why did I write it like this?
Individual * SimulatedAnnealer::getNeighbour(Individual * target) {
/*	uniform_int_distribution<int> neighbourDistribution(0, genomeLength-1);
	int choice = neighbourDistribution(generator);

	// Make sure we're not picking identical values over and over again
	for (int i = 0; i < genomeLength && neighbours[choice] == NULL; i++) {
		choice = neighbourDistribution(generator);
	}

	if (neighbours[choice] == NULL) return target->deepCopy();*/

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
