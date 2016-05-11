#include "nodes/SANode/schedules/LinearTempSchedule.hpp"

LinearTempSchedule::LinearTempSchedule(
	float initialTemp,
	int hoverTime,
	int iterationsToZero
) : TemperatureSchedule(initialTemp, hoverTime, iterationsToZero, "Linear") {}

float LinearTempSchedule::currentTemp(int currentIteration) {
	float frac = initialTemp/(float)iterationsToZero;

	if (currentIteration % hoverTime == 0) {
		currentTemperature = (currentIteration < iterationsToZero) ? 
			initialTemp - (frac*currentIteration) : 0;
	}

	return currentTemperature;
}
