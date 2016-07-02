#include "nodes/SANode/schedules/LinearTempSchedule.hpp"

LinearTempSchedule::LinearTempSchedule(
	float initialTemp,
	unsigned int hoverTime,
	unsigned int iterationsToZero
) : TemperatureSchedule(initialTemp, hoverTime, iterationsToZero, "Linear") {}

float LinearTempSchedule::currentTemp(unsigned int currentIteration) {
	float frac = initialTemp/(float)iterationsToZero;

	if (currentIteration % hoverTime == 0) {
		currentTemperature = (currentIteration < iterationsToZero) ? 
			initialTemp - (frac*currentIteration) : 0;
	}

	return currentTemperature;
}
