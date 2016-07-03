#include "../NestedObjective.hpp"
#pragma once

class MetaPopulationObjective : public NestedObjective {
	private:

	protected:

	public:
	MetaPopulationObjective(ObjectiveFunction * flattenedObjective);
	float checkFitness(Genome * genome);
};
