#include "../core/gc/NodeDeallocator.hpp"
#include "../nodes/SANode/SANode.hpp"
#include <vector>

class SANodeDeallocator : public NodeDeallocator {
	private:

	protected:

	public:
	SANodeDeallocator();
	~SANodeDeallocator();

	bool canDeleteNode(PopulationNode * node);
	void deleteNodes();
};