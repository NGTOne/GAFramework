#ifndef core_EA_BehaviourObject
#define core_EA_BehaviourObject

#include "gc/NodeGarbageCollector.hpp"
class NodeGarbageCollector;

class EABehaviourObject {
	private:

	protected:

	public:
	virtual ~EABehaviourObject() {};
	virtual void registerInternalObjects(
		NodeGarbageCollector & collector
	)=0;
};

#endif
