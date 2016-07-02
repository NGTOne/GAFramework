#include "nodes/SANode/schedules/ExponentialTempSchedule.hpp"

ExponentialTempSchedule::ExponentialTempSchedule(
	float initialTemp,
	float alpha,
	unsigned int hoverTime,
	unsigned int iterationsToZero
) : TemperatureSchedule(
	initialTemp,
	hoverTime,
	iterationsToZero,
	"Exponential"
) {
	this->alpha = alpha;
}

float ExponentialTempSchedule::currentTemp(unsigned int currentIteration) {
	if (currentIteration % hoverTime == 0) {
		currentTemperature = alpha * currentTemperature;
	}

	return currentTemperature;
}
