#include "../PopulationNode.hpp"
#include <vector>
#pragma once

class NodeDeallocator {
	private:

	protected:
	vector<PopulationNode*> nodes;

	public:
	NodeDeallocator();
	~NodeDeallocator();

	virtual bool canDeleteNode(PopulationNode * node)=0;
	void registerNode(PopulationNode * node);

	virtual void deleteNodes()=0;
};
