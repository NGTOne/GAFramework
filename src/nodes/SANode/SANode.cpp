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

int SANode::compareNeighbourliness(GenomeTemplate base, GenomeTemplate target) {
	Genome flattenedBase = Genome(base, 0).flattenGenome();
	Genome flattenedTarget = Genome(target, 0).flattenGenome();
	return flattenedBase.difference(&flattenedTarget);
}

std::vector<Genome*> SANode::getLocusNeighbours(
	Genome * target,
	unsigned int index
) {
	std::vector<Genome*> neighbours;
	GenomeTemplate templ = target->getTemplate();
	Locus * locus = templ.getLocus(index);

	unsigned int gene = templ.getGene(index);
	if (!locus->isConstructive()) {
		if (gene < templ.getLocus(index)->topIndex())
			neighbours.push_back(new Genome(
				GenomeTemplate(templ).set(gene + 1, index),
				target->getSpeciesNode()
			));
		if (gene > 0)
			neighbours.push_back(new Genome(
				GenomeTemplate(templ).set(gene - 1, index),
				target->getSpeciesNode()
			));
	} else {
		Genome * nearestKnownNeighbour;
		unsigned int top = templ.getLocus(index)->topIndex();
		int lowestDiff = 0, diff = 0;
		for (unsigned int i = 0; i <= top; i++) {
			if (i == gene) continue;
			GenomeTemplate newTempl = GenomeTemplate(templ)
				.set(i, index);
			diff = this->compareNeighbourliness(templ, newTempl);

			if ((diff < lowestDiff && diff > 0)
				|| lowestDiff == 0
			) {
				delete(nearestKnownNeighbour);
				nearestKnownNeighbour = new Genome(
					newTempl,
					target->getSpeciesNode()
				);
				lowestDiff = diff;
			}
		}

		neighbours.push_back(lowestDiff > 0 ?
			nearestKnownNeighbour : new Genome(target));
	}

	return neighbours;
}

Genome * SANode::getNeighbour(Genome * target) {
	vector<Genome*> neighbours = this->getLocusNeighbours(
		target,
		HierRNG::index(target->genomeLength() - 1)
	);
	unsigned int choice = HierRNG::index(neighbours.size() - 1);
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

		if (HierRNG::zeroOne<double>() < probability) {
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
