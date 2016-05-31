#include "systems/niching/Crowding.hpp"
#include <algorithm>

std::vector<unsigned int> Crowding::getIndices(
	std::vector<Genome*> initialPopulation,
	std::vector<Genome*> newPopulation
) {
	std::vector<unsigned int> indices;
	std::vector<int> differences(initialPopulation.size(), 0);
	int highestValue, lowestValue;
	unsigned int lowestIndex = 0;

	for (unsigned int i = 0; i < newPopulation.size(); i++) {
		highestValue = lowestIndex = 0;

		for (unsigned int k = 0; k < initialPopulation.size(); k++) {
			differences[k] = newPopulation[i]->difference(
				initialPopulation[k]
			);
			if (differences[k] > highestValue)
				highestValue = differences[k];
		}

		lowestValue = highestValue;

		for (unsigned int k = 0; k < initialPopulation.size(); k++) {
			if (differences[k] <= lowestValue) {
				if (find(indices.begin(), indices.end(), k)
					!= indices.end()
				) {
					lowestValue = differences[k];
					lowestIndex = k;
				}
			}
		}

		indices.push_back(lowestIndex);
	}
	return indices;
}
