#include "secondary-pop-nodes/annealer/SimulatedAnnealer.hpp"
#include <string>
#include <sstream>
#include <random>

using namespace std;

SimulatedAnnealer::SimulatedAnnealer(
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator
) : PopulationNode(
	1,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

SimulatedAnnealer::SimulatedAnnealer(
	int populationSize,
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator
) : PopulationNode(
	populationSize,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

SimulatedAnnealer::SimulatedAnnealer(
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator,
	unsigned seed
) : PopulationNode(
	1,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	seed,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

SimulatedAnnealer::SimulatedAnnealer(
	int populationSize,
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator,
	unsigned seed
) : PopulationNode(
	populationSize,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	seed,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

void SimulatedAnnealer::init(bool maximize, TemperatureSchedule * schedule) {
	this->maximize = maximize;
	this->schedule = schedule;
}

Individual ** SimulatedAnnealer::newPopulation() {
	Individual ** population = (Individual**)malloc(
		sizeof(Individual*)*populationSize
	);

	for (int i = 0; i < populationSize; i++) {
		population[i] = getNeighbour(myPopulation[i]);
	}

	return population;
}

Individual * SimulatedAnnealer::getNeighbour(Individual * target) {
	Individual * temp;

	uniform_real_distribution<double> goingWrongWayChanceDist(0.0, 1.0);
}
