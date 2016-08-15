#ifndef CORE_EVAL_ObjectiveFunction
#define CORE_EVAL_ObjectiveFunction

#include <string>
#include "../Genome.hpp"
#include "../EABehaviourObject.hpp"

class ObjectiveFunction : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~ObjectiveFunction();
	virtual float checkFitness(Genome * genome)=0;
	virtual bool isApportioning();
	virtual bool isNested();
};
#endif
