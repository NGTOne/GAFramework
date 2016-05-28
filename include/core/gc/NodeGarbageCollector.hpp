#include "../PopulationNode.hpp"
#include "NodeDeallocator.hpp"
#include <vector>

class NodeGarbageCollector {
	private:

	protected:
	std::vector<NodeDeallocator*> deallocators;

	public:
	NodeGarbageCollector();
	~NodeGarbageCollector();

	void deleteNodes(std::vector<PopulationNode*> nodes);
};
