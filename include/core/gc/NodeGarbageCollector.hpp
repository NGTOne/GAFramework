#ifndef CORE_GC_NodeGC
#define CORE_GC_NodeGC
#include "../EABehaviourObject.hpp"
#include <vector>
#include <set>
#pragma once

class EABehaviourObject;

class NodeGarbageCollector {
	private:

	protected:
	std::set<EABehaviourObject*> objects;

	public:
	NodeGarbageCollector();
	~NodeGarbageCollector();

	void cleanUp();

	void registerObject(EABehaviourObject * object);

	template <typename T>
	void registerObjects(std::vector<T*> objects);
};

template <typename T>
void NodeGarbageCollector::registerObjects(std::vector<T*> objects) {
	if (std::is_base_of<EABehaviourObject, T>::value)
		for (unsigned int i = 0; i < objects.size(); i++)
			this->registerObject(objects[i]);
}

#endif
#pragma once
