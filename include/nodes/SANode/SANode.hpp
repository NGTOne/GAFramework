#include "TemperatureSchedule.hpp"
#include "../../core/PopulationNode.hpp"
#include "../../core/Genome.hpp"
#include "../../core/GenomeTemplate.hpp"
#include <string>
#include <vector>
#include <random>
#pragma once

#define SA_TYPE "annealer"

class SANode : public PopulationNode {
	private:

	protected:
	TemperatureSchedule * schedule;
	bool maximize;

	bool readOnce;

	int compareNeighbourliness(GenomeTemplate base, GenomeTemplate target);
	Genome* getNeighbour(Genome* target);
	std::vector<Genome*> getLocusNeighbours(
		Genome* target,
		unsigned int index
	);
	void init(
		TemperatureSchedule * schedule,
		bool maximize
	);

	public:
	SANode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		TemperatureSchedule * schedule,
		bool maximize
	);

	SANode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		unsigned int accelerationFactor,
		TemperatureSchedule * schedule,
		bool maximize
	);

	SANode(
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		TemperatureSchedule * schedule,
		bool maximize
	);

	SANode(
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		unsigned int accelerationFactor,
		TemperatureSchedule * schedule,
		bool maximize
	);
	virtual void registerInternalObjects();

	virtual std::vector<Genome*> getNextPopulation();
	std::string toString();
	node_type_t type();

	TemperatureSchedule * getSchedule();

	PopulationNode * duplicate(std::string newNodeName);
};
