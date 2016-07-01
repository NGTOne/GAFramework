#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"

using namespace std;

int findLongestPath(Genome * genome, unsigned int & longestPathIndex) {
	Genome flattened = genome->flattenGenome();
	int longestPathLength = 0, currentPathLength = 0;
	unsigned int currentPathIndex, currentDigit;

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
	unsigned int bitBucket;
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
	unsigned int recipientStartIndex,
	std::vector<unsigned int> relevantRecipientIndices,
	int providerFitness
) {
	unsigned int longestPathLocation;
	unsigned int longestPathLength =
		findLongestPath(provider, longestPathLocation);
	unsigned int longestPathEndLocation =
		longestPathLocation + longestPathLength;
	unsigned int recipientEndLocation =
		recipientStartIndex + recipient->flattenedGenomeLength();

	if (recipientEndLocation < longestPathLocation)
		return 0;

	if (recipientStartIndex > longestPathEndLocation)
		return 0;

	unsigned int totalPathOverlap = 0, currentLocation;
	for (unsigned int i = 0; i < relevantRecipientIndices.size(); i++) {
		currentLocation = relevantRecipientIndices[i];
		if (
			currentLocation >= longestPathLocation
			&& currentLocation < longestPathEndLocation
			&& provider->indexIs<int>(currentLocation, 1)
			&& recipient->indexIs<int>(
				currentLocation - recipientStartIndex,
				1
			)
		) totalPathOverlap += 1;
	}

	return totalPathOverlap;
}
