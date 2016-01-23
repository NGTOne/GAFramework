#include "secondary-pop-nodes/annealer/schedules/LinearTempSchedule.hpp"

LinearTempSchedule::LinearTempSchedule(
	double initialTemp,
	int iterationsToZero
) : TemperatureSchedule(initialTemp, iterationsToZero, "Linear") {}

double LinearTempSchedule::currentTemp(int currentIteration) {
	double frac = initialTemp/(double)iterationsToZero;

	return (currentIteration < iterationsToZero) ? 
		initialTemp - (frac*currentIteration) : 0;
}
