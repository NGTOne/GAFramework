#include "nodes/EANode/mutations/GaussianMutation.hpp"
#include "core/utils/HierRNG.hpp"
#include <chrono>
#include <random>

GaussianMutation::GaussianMutation(double stdDev) {
	this->init(0, stdDev, false);
}

GaussianMutation::GaussianMutation(
	double mean,
	double stdDev
) : MutationOperation() {
	this->init(mean, stdDev, false);
}

GaussianMutation::GaussianMutation(
	double mean,
	double stdDev,
	bool endReflection
) : MutationOperation() {
	this->init(mean, stdDev, endReflection);
}

GaussianMutation::GaussianMutation(
	double mean,
	double stdDev,
	double mutationRate
) : MutationOperation(mutationRate) {
	this->init(mean, stdDev, false);
}

GaussianMutation::GaussianMutation(
	double mean,
	double stdDev,
	bool endReflection,
	double mutationRate
) : MutationOperation(mutationRate) {
	this->init(mean, stdDev, endReflection);
}

void GaussianMutation::init(double mean, double stdDev, bool endReflection) {
	this->mean = mean;
	this->stdDev = stdDev;
	this->endReflection = endReflection;
}

Gene* GaussianMutation::newLocusValue(Gene* current) {
	double addend = HierRNG::gaussian(this->mean, this->stdDev);
	double newIndex = current->getIndex() + addend;

	Locus* locus = current->getLocus();
	if (!this->endReflection)
		return current->copy(locus->closestIndex(newIndex));

	while (locus->outOfRange(newIndex)) {
		double topIndex = locus->topIndex();
		double bottomIndex = locus->bottomIndex();
		if (newIndex > topIndex) {
			newIndex = topIndex - (newIndex - topIndex);
		} else if (newIndex < bottomIndex) {
			newIndex = bottomIndex - (newIndex - bottomIndex);
		}
	}

	return current->copy(newIndex);
}
