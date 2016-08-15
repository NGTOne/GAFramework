#ifndef core_EABehaviourObject
#define core_EABehaviourObject

#include "utils/HierGC.hpp"
class HierGC;

class EABehaviourObject {
	private:

	protected:

	public:
	virtual ~EABehaviourObject() {};
	virtual void registerInternalObjects() {};
};

#endif
