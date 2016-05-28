#include "../nodes/EANode/SelectionStrategy.hpp"
#include <string>
#include <vector>
#pragma once

class RandomSelection : public SelectionStrategy {
	private:

	protected:

	public:
	RandomSelection();
        
	int getParent(
		std::vector<Genome*> population,
		std::vector<int> fitnesses
	);
	std::string toString();
};
