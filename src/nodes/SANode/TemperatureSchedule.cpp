#include "nodes/SANode/TemperatureSchedule.hpp"
#include <string>
#include <sstream>

using namespace std;

TemperatureSchedule::TemperatureSchedule(
	float initialTemp,
	int hoverTime,
	int iterationsToZero,
	string name
) {
	this->initialTemp = initialTemp;
	this->hoverTime = hoverTime;
	this->iterationsToZero = iterationsToZero;
	this->name = name;
	this->currentTemperature = initialTemp;
}

string TemperatureSchedule::toString() {
	stringstream ss;

	ss << "Name: " << name
	<< "\nInitial temperature: " << initialTemp
	<< "\nFreezing time: " << iterationsToZero << " iterations"
	<< "\n";

	return ss.str();
}
