#include "apportionment-func/SameFitnessApportionmentFunction.hpp"

float SameFitnessApportionmentFunction::apportionFitness(
	Genome * recipient,
	Genome * provider,
	unsigned int recipientStartIndex,
	std::vector<unsigned int> relevantRecipientIndices,
	float providerFitness
) {
	return providerFitness;
}
