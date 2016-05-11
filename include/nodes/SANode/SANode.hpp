#include "TemperatureSchedule.hpp"
#include "../../core/PopulationNode.hpp"
#include "../../core/Genome.hpp"
#include <string>
#include <vector>
#pragma once

class SANode : public PopulationNode {
	private:

	protected:
	TemperatureSchedule * schedule;
	bool maximize;

	int compareNeighbourliness(Genome * base, Genome * target);
	Genome * getNeighbour(Genome * target);
	std::vector<Genome*> getAllNeighbours(Genome * target);
	void init(
		bool maximize,
		TemperatureSchedule * schedule
	);

	public:
	SANode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		TemperatureSchedule * schedule,
		bool maximize
	);

	SANode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		bool maximize
	);

	SANode(
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		TemperatureSchedule * schedule,
		bool maximize
	);

	SANode(
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		bool maximize
	);

	virtual std::vector<Genome*> getNextPopulation();
	std::string toString();
};
