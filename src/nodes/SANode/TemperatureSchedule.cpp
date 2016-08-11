#include "nodes/SANode/TemperatureSchedule.hpp"
#include <string>
#include <sstream>

TemperatureSchedule::TemperatureSchedule(
	float initialTemp,
	unsigned int hoverTime,
	unsigned int iterationsToZero,
	std::string name
) {
	this->initialTemp = initialTemp;
	this->hoverTime = hoverTime;
	this->iterationsToZero = iterationsToZero;
	this->name = name;
	this->currentTemperature = initialTemp;
}

TemperatureSchedule::~TemperatureSchedule() {}

std::string TemperatureSchedule::toString() {
	std::stringstream ss;

	ss << "Name: " << this->name
	<< "\nInitial temperature: " << this->initialTemp
	<< "\nFreezing time: " << this->iterationsToZero << " iterations"
	<< "\n";

	return ss.str();
}
