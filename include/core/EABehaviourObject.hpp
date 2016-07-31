#ifndef core_EA_BehaviourObject
#define core_EA_BehaviourObject

#include "HierGC.hpp"
class HierGC;

class EABehaviourObject {
	private:

	protected:

	public:
	virtual ~EABehaviourObject()=0;
	virtual void registerInternalObjects() {};
};

#endif
