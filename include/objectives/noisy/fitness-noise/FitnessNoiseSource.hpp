#include <random>
#include "../../../core/EABehaviourObject.hpp"
#pragma once

class FitnessNoiseSource : public EABehaviourObject {
	private:

	protected:
	FitnessNoiseSource();

	public:
	virtual void registerInternalObjects(NodeGarbageCollector & collector);
	virtual float addNoise(float cleanFitness)=0;
};
