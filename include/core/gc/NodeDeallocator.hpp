#include "../PopulationNode.hpp"
#include <vector>
#include <set>
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

	template<typename T>
	void clearSet(typename std::set<T> target);
};
