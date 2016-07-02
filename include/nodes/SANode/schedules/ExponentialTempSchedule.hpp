#pragma once
#include "../TemperatureSchedule.hpp"

class ExponentialTempSchedule : public TemperatureSchedule {
	private:

	protected:
	float alpha;

	public:
	ExponentialTempSchedule(
		float initialTemp,
		float alpha,
		unsigned int hoverTime,
		unsigned int iterationsToZero
	);

	float currentTemp(unsigned int currentIteration);
};
