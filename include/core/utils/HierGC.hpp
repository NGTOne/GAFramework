#ifndef CORE_UTILS_NodeGC
#define CORE_UTILS_NodeGC

#include "../EABehaviourObject.hpp"
#include <vector>
#include <set>

class EABehaviourObject;

class HierGC {
	private:

	protected:
	static std::set<EABehaviourObject*> objects;

	public:
	static void cleanUp();

	static void registerObject(EABehaviourObject * object);

	template <typename T>
	static void registerObjects(std::vector<T*> objects);
};

template <typename T>
void HierGC::registerObjects(std::vector<T*> objects) {
	if (std::is_base_of<EABehaviourObject, T>::value)
		for (unsigned int i = 0; i < objects.size(); i++)
			HierGC::registerObject(objects[i]);
}

#endif
