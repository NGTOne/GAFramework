#pragma once
#include "TemperatureSchedule.hpp"

class LinearTempSchedule : public TemperatureSchedule {
	private:

	protected:

	public:
	LinearTempSchedule(
		float initialTemp,
		int hoverTime,
		int iterationsToZero
	);

	float currentTemp(int currentIteration);
};
