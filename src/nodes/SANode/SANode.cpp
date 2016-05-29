#include "nodes/SANode/SANode.hpp"
#include "core/Locus.hpp"
#include <string>
#include <sstream>
#include <random>
#include <cmath>
#include <chrono>

using namespace std;

SANode::SANode(
	int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	populationSize,
	loci,
	objectives,
	populationToString,
	conditions,
	name
) {
	init(schedule, maximize);
}

SANode::SANode(
	int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	populationSize,
	loci,
	objectives,
	populationToString,
	conditions,
	name,
	accelerationFactor
) {
	init(schedule, maximize);
}

SANode::SANode(
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	1,
	loci,
	objectives,
	populationToString,
	conditions,
	name
) {
	init(schedule, maximize);
}

SANode::SANode(
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	bool maximize
) : PopulationNode(
	1,
	loci,
	objectives,
	populationToString,
	conditions,
	name,
	accelerationFactor
) {
	init(schedule, maximize);
}

void SANode::init(TemperatureSchedule * schedule, bool maximize) {
	this->maximize = maximize;
	this->schedule = schedule;

	seed = chrono::system_clock::now().time_since_epoch().count();
	generator = mt19937(seed);
	readOnce = false;
}

int SANode::compareNeighbourliness(Genome * base, Genome * target) {
	Genome flattenedBase = base->flattenGenome();
	Genome flattenedTarget = target->flattenGenome();
	return flattenedBase.difference(&flattenedTarget);
}

// TODO: Break this down further at some point
// TODO: Make this more efficient
vector<Genome*> SANode::getAllNeighbours(Genome * target) {
	vector<Genome*> neighbours;
	vector<Locus*> loci = target->getLoci();
	vector<int> rawGenes = target->getGenome();
	vector<int> tempGenes = rawGenes;

	for (int i = 0; i < target->genomeLength(); i++) {
		if (loci[i]->isConstructive()) {
			Genome * nearestKnownNeighbour, * tempGenome;
			int top = loci[i]->topIndex();
			int lowestDiff = 0, diff = 0;

			for (int k = 0; k <= top; k++) {
				// So we're not checking against ourselves
				if (rawGenes[i] == k && k++ >= top) break;

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
	int choice = neighbourDist(generator);
	Genome * neighbour = neighbours[choice];

	for (int i = 0; i < neighbours.size(); i++) {
		if (i != choice) delete(neighbours[i]);
	}

	int neighbourFitness = this->evaluateFitness(neighbour);
	int targetFitness = this->evaluateFitness(target);

	if ((this->maximize && targetFitness < neighbourFitness) ||
		(!this->maximize && targetFitness > neighbourFitness)) {
		return neighbour;
	} else {
		float currentTemp = this->schedule->currentTemp(
			currentIteration
		);

		if (currentTemp == 0) {
			delete(neighbour);
			return new Genome(target);
		}

		float delta = this->maximize ? neighbourFitness - targetFitness
			: targetFitness - neighbourFitness;

		float probability = exp(delta/currentTemp);

		uniform_real_distribution<float> goingWrongWayDist(0, 1);

		if (goingWrongWayDist(this->generator) < probability) {
			return neighbour;
		} else {
			return new Genome(target);
		}
	}
}

vector<Genome*> SANode::getNextPopulation() {
	vector<Genome*> newPopulation;
	for (int i = 0; i < population.size(); i++) {
		newPopulation.push_back(getNeighbour(population[i]));
		delete(population[i]);
	}

	return newPopulation;
}

string SANode::toString() {
	stringstream ss;

	ss << "Population size: " << population.size() << "\n";
	ss << populationStrings();

	if (!readOnce) ss << "Seed: " << seed << "\n";
	readOnce = true;

	return ss.str();
}

node_type_t SANode::type() {
	return SA_TYPE;
}

TemperatureSchedule * SANode::getSchedule() {
	return this->schedule;
}
