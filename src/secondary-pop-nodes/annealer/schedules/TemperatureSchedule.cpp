#include "secondary-pop-nodes/annealer/schedules/TemperatureSchedule.hpp"
#include <string>
#include <sstream>

using namespace std;

TemperatureSchedule::TemperatureSchedule(
	double initialTemp,
	int iterationsToZero,
	string name
) {
	this->initialTemp = initialTemp;
	this->iterationsToZero = iterationsToZero;
	this->name = name;
}

string TemperatureSchedule::toString() {
	stringstream ss;

	ss << "Name: " << name
	<< "\nInitial temperature: " << initialTemp
	<< "\nFreezing time: " << iterationsToZero << " iterations"
	<< "\n";

	return ss.str();
}
