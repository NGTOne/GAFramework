#include "schedules/TemperatureSchedule.hpp"
#include "../../core/PopulationNode.hpp"
#include <string.h>
#pragma once

class SimulatedAnnealer : public PopulationNode {
	private:

	protected:
	TemperatureSchedule * schedule;
	bool maximize;

	Individual * getNeighbour(Individual * target);
	void init(
		int populationSize,
		Individual * templateIndividual,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		unsigned seed
	);

	public:
	SimulatedAnnealer(
		Individual * templateIndividual,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule
	);

	SimulatedAnnealer(
		int populationSize,
		Individual * templateIndividual,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule
	);

	SimulatedAnnealer(
		Individual * templateIndividual,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		unsigned seed
	);

	SimulatedAnnealer(
		int populationSize,
		Individual * templateIndividual,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		unsigned seed
	);

	void nextGeneration();
	std::string toString();
};
