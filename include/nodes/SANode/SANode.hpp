#include "schedules/TemperatureSchedule.hpp"
#include "../../core/PopulationNode.hpp"
#include "../../core/Solution.hpp"
#include <string.h>
#pragma once

class SANode : public PopulationNode {
	private:

	protected:
	TemperatureSchedule * schedule;
	bool maximize;

	int compareNeighbourliness(Solution * base, Solution * target);
	Solution * getNeighbour(Solution * target);
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

	virtual void nextIteration();
	std::string toString();
};
