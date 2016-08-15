#ifndef CORE_META_MetaPopulationObjective
#define CORE_META_MetaPopulationObjective

#include "../eval/NestedObjective.hpp"

class MetaPopulationObjective : public NestedObjective {
	private:

	protected:

	public:
	MetaPopulationObjective(ObjectiveFunction * flattenedObjective);
	float checkFitness(Genome * genome);
};

#endif
