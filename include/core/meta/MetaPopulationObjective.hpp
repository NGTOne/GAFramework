#include "MetaPopulationFunction.hpp"
#include "../ObjectiveFunction.hpp"
#pragma once

class MetaPopulationObjective :
	public ObjectiveFunction,
	public MetaPopulationFunction
{
	private:

	protected:
	ObjectiveFunction * flattenedObjective;

	public:
	MetaPopulationObjective(ObjectiveFunction * flattenedObjective);
	int checkFitness(Genome * genome);
};
