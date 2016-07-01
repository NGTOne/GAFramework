#include "../nodes/EANode/SelectionStrategy.hpp"
#include <string>
#include <vector>
#pragma once

class RandomSelection : public SelectionStrategy {
	private:

	protected:

	public:
	RandomSelection();
        
	unsigned int getParent(
		std::vector<Genome*> population,
		std::vector<float> fitnesses
	);
	std::string toString();
};
