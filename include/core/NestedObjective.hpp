#include "ObjectiveFunction.hpp"
#include <vector>

class NestedObjective: public ObjectiveFunction {
	private:

	protected:
	ObjectiveFunction * innerObjective;
	float checkInnerFitness(Genome * target);

	public:
	NestedObjective(ObjectiveFunction * innerObjective);
	bool isNested();
	std::vector<ObjectiveFunction*> getInner();
};
