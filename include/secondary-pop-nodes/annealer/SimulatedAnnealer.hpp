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
		bool maximize,
		TemperatureSchedule * schedule
	);

	public:
	SimulatedAnnealer(
		Individual * templateIndividual,
		bool maximize,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		EndCondition * condition,
		FitnessPropagator * propagator
	);

	SimulatedAnnealer(
		int populationSize,
		Individual * templateIndividual,
		bool maximize,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		EndCondition * condition,
		FitnessPropagator * propagator
	);

	SimulatedAnnealer(
		Individual * templateIndividual,
		bool maximize,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		EndCondition * condition,
		FitnessPropagator * propagator,
		unsigned seed
	);

	SimulatedAnnealer(
		int populationSize,
		Individual * templateIndividual,
		bool maximize,
		int maxIterations,
		int accelerationFactor,
		TemperatureSchedule * schedule,
		EndCondition * condition,
		FitnessPropagator * propagator,
		unsigned seed
	);

	Individual ** newPopulation();
	std::string toString();
};
