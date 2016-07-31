#include <random>
#include "../../../core/EABehaviourObject.hpp"
#pragma once

class FitnessNoiseSource : public EABehaviourObject {
	private:

	protected:
	FitnessNoiseSource();

	public:
	virtual float addNoise(float cleanFitness)=0;
};
