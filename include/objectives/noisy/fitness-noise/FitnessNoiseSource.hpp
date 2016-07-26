#include <random>
#include "../../../core/EABehaviourObject.hpp"
#pragma once

class FitnessNoiseSource : public EABehaviourObject {
	private:

	protected:
	std::mt19937 generator;

	FitnessNoiseSource();
	FitnessNoiseSource(unsigned int seed);

	public:
	virtual void registerInternalObjects(NodeGarbageCollector & collector);
	virtual float addNoise(float cleanFitness)=0;
};
