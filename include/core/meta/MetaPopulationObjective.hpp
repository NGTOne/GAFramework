#include "../ObjectiveFunction.hpp"
#pragma once

class MetaPopulationObjective : public ObjectiveFunction {
	private:

	protected:
	ObjectiveFunction * flattenedObjective;

	public:
	MetaPopulationObjective(ObjectiveFunction * flattenedObjective);
	float checkFitness(Genome * genome);
};
