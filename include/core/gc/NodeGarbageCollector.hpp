#ifndef CORE_GC_NodeGC
#define CORE_GC_NodeGC
#include "../PopulationNode.hpp"
#include "../EABehaviourObject.hpp"
#include <vector>
#include <set>
#pragma once

class NodeGarbageCollector {
	private:

	protected:
	std::set<EABehaviourObject*> objects;

	public:
	NodeGarbageCollector();
	~NodeGarbageCollector();

	void cleanUp();

	void registerObject(EABehaviourObject * object);
	void registerObjects(std::vector<EABehaviourObject*> objects);
};

#endif
#pragma once
