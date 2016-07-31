#include "nodes/SANode/TemperatureSchedule.hpp"
#include <string>
#include <sstream>

using namespace std;

TemperatureSchedule::TemperatureSchedule(
	float initialTemp,
	unsigned int hoverTime,
	unsigned int iterationsToZero,
	string name
) {
	this->initialTemp = initialTemp;
	this->hoverTime = hoverTime;
	this->iterationsToZero = iterationsToZero;
	this->name = name;
	this->currentTemperature = initialTemp;
}

TemperatureSchedule::~TemperatureSchedule() {}

string TemperatureSchedule::toString() {
	stringstream ss;

	ss << "Name: " << name
	<< "\nInitial temperature: " << initialTemp
	<< "\nFreezing time: " << iterationsToZero << " iterations"
	<< "\n";

	return ss.str();
}
