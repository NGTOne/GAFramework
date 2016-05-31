#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"

using namespace std;

int findLongestPath(Genome * genome, int & longestPathIndex) {
	Genome flattened = genome->flattenGenome();
	int longestPathLength = 0, currentPathLength = 0;
	int currentPathIndex, currentDigit;

	for (unsigned int i = 0; i < flattened.genomeLength(); i++) {
		currentDigit = flattened.getIndex<int>(i);
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

LongestFragmentFitness::LongestFragmentFitness() : ObjectiveFunction() {}

int LongestFragmentFitness::checkFitness(Genome * genome) {
	int bitBucket;
	return findLongestPath(genome, bitBucket);
}

string LongestFragmentToString::toString(Genome * genome) {
	stringstream ss;
	Genome flattened = genome->flattenGenome();

	for (unsigned int i = 0; i < flattened.genomeLength(); i++)
		ss << flattened.getIndex<int>(i);

	return ss.str();
}

int LongestFragmentApportionment::apportionFitness(
	Genome * recipient,
	Genome * provider,
	int providerFitness
) {
	int recipientStartIndex = provider->getFlattenedIndex(recipient);
	int longestPathLocation;
	int longestPathLength = findLongestPath(provider, longestPathLocation);
	int longestPathEndLocation = longestPathLocation + longestPathLength;
	int recipientEndLocation =
		recipientStartIndex + recipient->genomeLength();

	if (recipientEndLocation < longestPathLocation)
		return 0;

	if (recipientStartIndex > longestPathEndLocation)
		return 0;

	int totalPathOverlap = 0;
	Genome flattenedRecipient = recipient->flattenGenome();

	int currentLocation;
	for (int i = 0; i < flattenedRecipient.genomeLength(); i++) {
		currentLocation = i + recipientStartIndex;
		if (
			currentLocation >= longestPathLocation
			&& currentLocation < longestPathEndLocation
		) {
			if (flattenedRecipient.indexIs<int>(i, 1))
				totalPathOverlap += 1;
		}
	}

	return totalPathOverlap;
}
