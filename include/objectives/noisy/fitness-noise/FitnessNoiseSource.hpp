#ifndef OBJECTIVES_NOISY_FITNESS_NOISE_FitnessNoiseSource
#define OBJECTIVES_NOISY_FITNESS_NOISE_FitnessNoiseSource

#include "../../../core/EABehaviourObject.hpp"

class FitnessNoiseSource : public EABehaviourObject {
	private:

	protected:
	FitnessNoiseSource();

	public:
	virtual float addNoise(float cleanFitness)=0;
};

#endif
