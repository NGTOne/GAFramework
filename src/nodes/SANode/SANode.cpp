#include "nodes/SANode/SANode.hpp"
#include "core/Locus.hpp"
#include "core/HierRNG.hpp"
#include <string>
#include <sstream>
#include <random>
#include <cmath>
#include <chrono>

using namespace std;

SANode::SANode(
	unsigned int populationSize,
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
	unsigned int populationSize,
	vector<Locus*> loci,
	vector<ObjectiveFunction*> objectives,
	ToStringFunction * populationToString,
	vector<EndCondition*> conditions,
	string name,
	unsigned int accelerationFactor,
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
	unsigned int accelerationFactor,
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

void SANode::registerInternalObjects(NodeGarbageCollector & collector) {
	PopulationNode::registerInternalObjects(collector);
	collector.registerObject(this->schedule);
}

void SANode::init(TemperatureSchedule * schedule, bool maximize) {
	this->maximize = maximize;
	this->schedule = schedule;
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
	vector<unsigned int> rawGenes = target->getGenome();
	vector<unsigned int> tempGenes = rawGenes;

	for (unsigned int i = 0; i < target->genomeLength(); i++) {
		if (loci[i]->isConstructive()) {
			Genome * nearestKnownNeighbour, * tempGenome;
			unsigned int top = loci[i]->topIndex();
			int lowestDiff = 0, diff = 0;

			for (unsigned int k = 0; k <= top; k++) {
				// So we're not checking against ourselves
				if (rawGenes[i] == k && k++ >= top) break;

				tempGenes = rawGenes;
				tempGenes[i] = k;
				tempGenome = new Genome(
					tempGenes,
					loci,
					target->getSpeciesNode()
				);

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
					new Genome(
						rawGenes,
						loci,
						target->getSpeciesNode()
					)
				);
			}

			tempGenes = rawGenes;
			if (!loci[i]->outOfRange(rawGenes[i]-1)) {
				tempGenes[i]--;
				neighbours.push_back(
					new Genome(
						rawGenes,
						loci,
						target->getSpeciesNode()
					)
				);
			}
		}
	}

	return neighbours;
}

Genome * SANode::getNeighbour(Genome * target) {
	vector<Genome*> neighbours = this->getAllNeighbours(target);
	unsigned int choice = HierRNG::uniformRandomNumber<
		unsigned int
	>(0, neighbours.size() - 1);
	Genome * neighbour = neighbours[choice];

	for (unsigned int i = 0; i < neighbours.size(); i++) {
		if (i != choice) delete(neighbours[i]);
	}

	float neighbourFitness = this->evaluateFitness(neighbour);
	float targetFitness = this->evaluateFitness(target);

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

		if (HierRNG::zeroOne() < probability) {
			return neighbour;
		} else {
			return new Genome(target);
		}
	}
}

vector<Genome*> SANode::getNextPopulation() {
	vector<Genome*> newPopulation;
	for (unsigned int i = 0; i < population.size(); i++) {
		newPopulation.push_back(getNeighbour(population[i]));
		delete(population[i]);
	}

	return newPopulation;
}

string SANode::toString() {
	stringstream ss;

	ss << "Population size: " << population.size() << "\n";
	ss << populationStrings();

	return ss.str();
}

node_type_t SANode::type() {
	return SA_TYPE;
}

TemperatureSchedule * SANode::getSchedule() {
	return this->schedule;
}

PopulationNode * SANode::duplicate(std::string newNodeName) {
	return new SANode(
		this->populationSize(),
		this->getCanonicalLoci(),
		this->getObjectives(),
		this->getToString(),
		this->getConditions(),
		newNodeName,
		this->accelerationFactor,
		this->getSchedule(),
		this->maximize
	);
}
