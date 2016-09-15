#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "LongestFragmentFitness.hpp"

using namespace std;

unsigned int findLongestPath(
	Genome * genome,
	unsigned int & longestPathIndex
) {
	Genome flattened = genome->flattenGenome();
	unsigned int longestPathLength = 0, currentPathLength = 0;
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

float LongestFragmentFitness::checkFitness(Genome * genome) {
	unsigned int bitBucket;
	return findLongestPath(genome, bitBucket);
}

LongestFragmentToString::LongestFragmentToString(
	HierarchicalToString::mode printMode
) : HierarchicalToString(printMode) {}

std::string LongestFragmentToString::stringifySegment(
	std::vector<Gene*> genes
) {
	stringstream ss;

	for (unsigned int i = 0; i < genes.size(); i++)
		ss << genes[i]->getValue<int>();

	return ss.str();
}

float LongestFragmentApportionment::apportionFitness(
	Genome * recipient,
	Genome * provider,
	unsigned int recipientStartIndex,
	std::vector<unsigned int> relevantRecipientIndices,
	float providerFitness
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
