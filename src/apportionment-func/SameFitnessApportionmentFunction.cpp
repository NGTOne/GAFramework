#include "apportionment-func/SameFitnessApportionmentFunction.hpp"

int SameFitnessApportionmentFunction::apportionFitness(
	Genome * recipient,
	Genome * provider,
	unsigned int recipientLocation,
	int providerFitness
) {
	return providerFitness;
}
