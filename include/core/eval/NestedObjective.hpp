#ifndef CORE_EVAL_NestedObjective
#define CORE_EVAL_NestedObjective

#include "ObjectiveFunction.hpp"
#include <vector>

class NestedObjective: public ObjectiveFunction {
	private:

	protected:
	ObjectiveFunction * innerObjective;
	Fitness checkInnerFitness(Genome* target);

	public:
	NestedObjective(ObjectiveFunction * innerObjective);
	virtual void registerInternalObjects();
	bool isNested();
	std::vector<ObjectiveFunction*> getInner();
};

#endif
