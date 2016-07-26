#ifndef CORE_ObjectiveFunction
#define CORE_ObjectiveFunction

#include <string>
#include "Genome.hpp"
#include "EABehaviourObject.hpp"

class ObjectiveFunction : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~ObjectiveFunction();
	virtual void registerInternalObjects(NodeGarbageCollector & collector);
	virtual float checkFitness(Genome * genome)=0;
	virtual bool isApportioning();
	virtual bool isNested();
};
#endif
