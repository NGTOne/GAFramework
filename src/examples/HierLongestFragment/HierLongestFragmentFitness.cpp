#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "HierLongestFragmentFitness.hpp"

using namespace std;

HierLongestFragmentFitness::HierLongestFragmentFitness() : ObjectiveFunction() {}

int HierLongestFragmentFitness::checkFitness(Genome * genome) {
	Genome flattened = genome->flattenGenome();
	int longestPathLength = 0, currentPathLength = 0;
	int currentPathIndex, longestPathIndex, currentDigit;
	vector<int> rawGenome = flattened.getGenome();
	vector<Locus*> loci = flattened.getLoci();

	for (int i = 0; i < flattened.genomeLength(); i++) {
		currentDigit = ((IntLocus*)loci[i])->getIndex(rawGenome[i]);
		currentPathIndex = i-currentPathLength;

		if (currentDigit == 1) {
			currentPathLength += 1;
		} else {
			if (currentPathLength > longestPathLength) {
				longestPathLength = currentPathLength;
				longestPathIndex = currentPathIndex;
			}
			currentPathLength = 0;
		}
	}

	if (currentPathLength > longestPathLength) {
		longestPathLength = currentPathLength;
		longestPathIndex = currentPathIndex;
	}

	return longestPathLength;
}

string HierLongestFragmentToString::toString(Genome * genome) {
	stringstream ss;
	Genome flattened = genome->flattenGenome();
	vector<int> rawGenome = flattened.getGenome();
	vector<Locus*> loci = flattened.getLoci();

	for (int i = 0; i < flattened.genomeLength(); i++)
		ss << ((IntLocus*)loci[i])->getIndex(rawGenome[i]);

	return ss.str();
}
