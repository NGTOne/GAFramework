#include "ObjectiveFunction.hpp"
#include <vector>
#pragma once

class NestedObjective: public ObjectiveFunction {
	private:

	protected:
	ObjectiveFunction * innerObjective;
	float checkInnerFitness(Genome * target);

	public:
	NestedObjective(ObjectiveFunction * innerObjective);
	virtual void registerInternalObjects();
	bool isNested();
	std::vector<ObjectiveFunction*> getInner();
};
