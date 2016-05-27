#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"

using namespace std;

LongestFragmentFitness::LongestFragmentFitness() : ObjectiveFunction() {}

int LongestFragmentFitness::checkFitness(Genome * genome) {
	int longestPathLength = 0, currentPathLength = 0;
	int currentPathIndex, longestPathIndex, currentDigit;
	vector<int> rawGenome = genome->getGenome();
	vector<Locus*> loci = genome->getLoci();

	for (int i = 0; i < genome->genomeLength(); i++) {
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

string LongestFragmentToString::toString(Genome * genome) {
	stringstream ss;
	vector<int> rawGenome = genome->getGenome();
	vector<Locus*> loci = genome->getLoci();

	for (int i = 0; i < genome->genomeLength(); i++)
		ss << ((IntLocus*)loci[i])->getIndex(rawGenome[i]);

	return ss.str();
}
