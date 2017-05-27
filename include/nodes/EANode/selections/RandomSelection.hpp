#ifndef NODES_EANODE_SELECTIONS_RandomSelection
#define NODES_EANODE_SELECTIONS_RandomSelection

#include "../SelectionStrategy.hpp"
#include <string>
#include <vector>

class RandomSelection : public SelectionStrategy {
	private:

	protected:

	public:
	RandomSelection();
        
	unsigned int getParent(
		std::vector<Genome*> population,
		std::vector<Fitness> fitnesses
	);
	std::string toString();
};

#endif
