#pragma once
#include <string>

class TemperatureSchedule {
	private:

	protected:
	double initialTemp;
	int iterationsToZero;
	std::string name;

	TemperatureSchedule(
		double initialTemp,
		int iterationsToZero,
		std::string name
	);

	public:
	virtual double currentTemp(int currentIteration)=0;
	virtual std::string toString();
};
