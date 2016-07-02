#include "apportionment-func/SameFitnessApportionmentFunction.hpp"

float SameFitnessApportionmentFunction::apportionFitness(
	Genome * recipient,
	Genome * provider,
	unsigned int recipientLocation,
	float providerFitness
) {
	return providerFitness;
}
