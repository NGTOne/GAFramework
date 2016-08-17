#include "core/utils/HierGC.hpp"
#include <algorithm>

std::set<EABehaviourObject*> HierGC::objects = std::set<EABehaviourObject*>();

void HierGC::cleanUp() {
	for (auto object : HierGC::objects) delete(object);
	HierGC::objects.clear();
}

void HierGC::registerObject(EABehaviourObject * object) {
	if (object != NULL) {
		object->registerInternalObjects();
		HierGC::objects.insert(object);
	}
}
