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
	void clearSet(std::set<T> target);
};

// Needs to be here, because it's used in many places
template <typename T>
void NodeDeallocator::clearSet(std::set<T> target) {
	std::vector<T> targetVector(target.begin(), target.end());
	for (int i = 0; i < targetVector.size(); i++) delete(targetVector[i]);
}
