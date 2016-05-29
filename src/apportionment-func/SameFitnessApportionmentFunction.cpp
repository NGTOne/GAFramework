#include "apportionment-func/SameFitnessApportionmentFunction.hpp"

int SameFitnessApportionmentFunction::apportionFitness(
	Genome * recipient,
	Genome * provider,
	int providerFitness
) {
	return providerFitness;
}
