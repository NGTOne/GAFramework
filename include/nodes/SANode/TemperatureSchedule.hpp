#pragma once
#include <string>

class TemperatureSchedule {
	private:

	protected:
	float initialTemp;
	int hoverTime;
	int iterationsToZero;
	float currentTemperature;
	std::string name;

	TemperatureSchedule(
		float initialTemp,
		int hoverTime,
		int iterationsToZero,
		std::string name
	);

	public:
	virtual float currentTemp(int currentIteration)=0;
	virtual std::string toString();
};
