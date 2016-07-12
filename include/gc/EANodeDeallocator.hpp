#include "../core/gc/NodeDeallocator.hpp"
#include "../nodes/EANode/EANode.hpp"
#include <vector>
#pragma once

class EANodeDeallocator : public NodeDeallocator {
	private:

	protected:

	public:
	EANodeDeallocator();
	~EANodeDeallocator();

	bool canDeleteNode(PopulationNode * node);
	void deleteNodes();
};
