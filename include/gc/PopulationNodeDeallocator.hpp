#include "../core/gc/NodeDeallocator.hpp"
#include "../core/PopulationNode.hpp"
#include <vector>
#pragma once

/*
* This deallocator does something a little different - rather than deleting the
* node itself, it will only remove all the elements that are common between all
* population nodes - objective functions, ToStrings, and so on
*/

class PopulationNodeDeallocator : public NodeDeallocator {
	private:

	protected:

	public:
	PopulationNodeDeallocator();
	~PopulationNodeDeallocator();

	bool canDeleteNode(PopulationNode * node);
	void deleteNodes();
};
