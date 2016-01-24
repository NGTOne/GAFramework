#pragma once
#include "TemperatureSchedule.hpp"

class LinearTempSchedule : public TemperatureSchedule {
	private:

	protected:

	public:
	LinearTempSchedule(double initialTemp, int iterationsToZero);

	double currentTemp(int currentIteration);
};
