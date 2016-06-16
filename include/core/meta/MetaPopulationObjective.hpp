#include "MetaPopulationFunction.hpp"
#pragma once

class MetaPopulationObjective : public MetaPopulationFunction {
	private:

	protected:
	ObjectiveFunction * flattenedObjective;

	public:
	MetaPopulationObjective(ObjectiveFunction * flattenedObjective);
	int checkFitness(Genome * genome);
};
