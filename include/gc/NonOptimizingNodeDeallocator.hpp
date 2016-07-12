#include "../core/gc/NodeDeallocator.hpp"
#include "../nodes/NonOptimizingNode.hpp"
#include <vector>
#pragma once

class NonOptimizingNodeDeallocator : public NodeDeallocator {
	private:

	protected:

	public:
	NonOptimizingNodeDeallocator();
	~NonOptimizingNodeDeallocator();

	bool canDeleteNode(PopulationNode * node);
	void deleteNodes();
};
