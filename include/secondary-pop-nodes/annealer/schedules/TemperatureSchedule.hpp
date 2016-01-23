#pragma once

class TemperatureSchedule {
	private:

	protected:
	double initialTemp;
	int iterationsToZero;

	public:
	TemperatureSchedule(double initialTemp, int iterationsToZero);

	virtual double currentTemp(int currentIteration)=0;
};
