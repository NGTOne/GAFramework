#pragma once
#include "TemperatureSchedule.hpp"

class ExponentialTempSchedule : public TemperatureSchedule {
	private:

	protected:
	float alpha;

	public:
	ExponentialTempSchedule(
		float initialTemp,
		float alpha,
		int hoverTime,
		int iterationsToZero
	);

	float currentTemp(int currentIteration);
};
