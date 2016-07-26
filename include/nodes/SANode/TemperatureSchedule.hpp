#pragma once
#include <string>
#include "../../core/EABehaviourObject.hpp"

class TemperatureSchedule : public EABehaviourObject {
	private:

	protected:
	float initialTemp;
	unsigned int hoverTime;
	unsigned int iterationsToZero;
	float currentTemperature;
	std::string name;

	TemperatureSchedule(
		float initialTemp,
		unsigned int hoverTime,
		unsigned int iterationsToZero,
		std::string name
	);

	public:
	virtual ~TemperatureSchedule();
	virtual void registerInternalObjects(NodeGarbageCollector & collector);
	virtual float currentTemp(unsigned int currentIteration)=0;
	virtual std::string toString();
};
