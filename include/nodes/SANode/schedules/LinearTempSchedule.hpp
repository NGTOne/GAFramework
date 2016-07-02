#pragma once
#include "../TemperatureSchedule.hpp"

class LinearTempSchedule : public TemperatureSchedule {
	private:

	protected:

	public:
	LinearTempSchedule(
		float initialTemp,
		unsigned int hoverTime,
		unsigned int iterationsToZero
	);

	float currentTemp(unsigned int currentIteration);
};
