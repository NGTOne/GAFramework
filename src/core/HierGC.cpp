#include "core/HierGC.hpp"
#include <algorithm>

void HierGC::cleanUp() {
	for (auto object : HierGC::objects) delete(object);
}

void HierGC::registerObject(EABehaviourObject * object) {
	object->registerInternalObjects();
	HierGC::objects.insert(object);
}
